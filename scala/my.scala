package GIFReader

import java.util.{MissingResourceException, IllegalFormatException}
import scodec._
import bits._
import scodec.codecs._
import java.nio.file.{Files, Paths}
import java.io._
import scodec.bits.ByteOrdering.LittleEndian
import scala.NoSuchElementException
import swing.{Panel, MainFrame, SimpleSwingApplication}
import java.awt.{Color, Graphics2D, Dimension}
import java.awt.image.BufferedImage

class DataPanel(args: Array[Array[Color]]) extends Panel {
  override def paintComponent(g: Graphics2D) {

    val height = args.map(_.length).max
    val width = args.length
    val dx = g.getClipBounds.width.toFloat  / width
    val dy = g.getClipBounds.height.toFloat / height
    for {
      x <- 0 until args.length
      y <- 0 until args(x).length
      x1 = (x * dx).toInt
      y1 = (y * dy).toInt
      x2 = ((x + 1) * dx).toInt
      y2 = ((y + 1) * dy).toInt
    }
    {
      args(x)(y) match {
        case c: Color => g.setColor(c)
        case _ => g.setColor(Color.WHITE)
      }
      g.fillRect(x1, y1, x2 - x1, y2 - y1)
    }
  }

}
  object Timer {
   def apply(interval: Int, repeats: Boolean = true)(op: => Unit) {
    val timeisout = new javax.swing.AbstractAction() {
      def actionPerformed(e : java.awt.event.ActionEvent) = op
    }
      val t = new javax.swing.Timer(interval, timeisout)
      t.setRepeats(repeats)
      t.start()
    }
  }

  object Pensil extends SimpleSwingApplication {

    case class gifhead (width: Int, height: Int, GCT_flag: Boolean, colorres: Int, SF: Boolean, GCT: Int, Bkground_color: Int, ratio: Int)

     case class image (LP: Int, TP: Int, width: Int, height: Int, LCT: Boolean, inplace_flag: Boolean, sort: Boolean, revbits: Int, LCT_size: Int)

     case class animation (method: Int, ui: Boolean, tc: Boolean, detention: Int, transcolor: Int)

     case class giffile (header: gifhead, globColorTable: Array[Int], imagedes: List[image], images: List[Array[Int]], animations: List[animation])


   def LZW(minr: Int, input: BitVect, CT: List[Int]): Array[Int] = {
     
     def Listof(list: List[Int], acc: List[Array[Int]]): List[Array[Int]] =
       if (list.isEmpty)    acc.reverse
        else     Listof(list.tail, Array(list.head) :: acc)


      def Itr(elemSize: Int, Pref: Array[Int], in: BitVect, table: List[Array[Int]], out: Array[Int], elemEnd: Int): Array[Int] = {
        
      val elem = in.take(elemSize).reverseBitOrder.toInt(false, LittleEndian)
      if (elem == elemEnd) 
        out
      
      else if (elem < table.length) {
        
        val Ntable = table ::: List((Pref :+ table(elem)(0)))
        val Nout = out ++ table(elem)
        
        Itr(1 + (Math.log(Ntable.length) / Math.log(2)).toInt, table(elem), in.drop(elemSize),
          Ntable, Nout, elemEnd)
      }
      else {
        
        val Ntable = table ::: List((Pref :+ Pref(0)))
        val Nout = out ++ (Pref :+ Pref(0))
        
        Itr(1 + (Math.log(Ntable.length) / Math.log(2)).toInt, Pref :+ Pref(0), in.drop(elemSize),
          Ntable, Nout, elemEnd)
      }
    }
     
    val elemClear = input.take(minr).reverseBitOrder.toInt(false, LittleEndian)
    val elemFirst = input.drop(minr).take(minr).reverseBitOrder.toInt(false, LittleEndian)
     
    Itr(minr, Array(CT(elemFirst)), input.drop(2 * minr), Listof(CT, Nil),
      Array(CT(elemFirst)), elemClear + 1)
  }
    
  def Decode(path: String): giffile = {

    val headerCodec = (uint16L :: uint16L :: bool :: uintL(3) :: bool :: uintL(3) :: uint8L :: uint8L).as[gifhead]
    val imageCodec = (uint16L :: uint16L :: uint16L :: uint16L :: bool :: bool :: bool :: uint2L :: uintL(3)).as[image]
    val animationCodec = (uintL(3) :: bool :: bool :: uint16L :: uint8L).as[animation]

    def crColorofTable(table: Array[Int], size: Int, Vect: BitVect): Array[Int] = {
      
      if (size == 0) 
        table
      
      else {
        
        val red = Vect.take(8).toInt(false, LittleEndian)
        val green = Vect.drop(8).take(8).toInt(false, LittleEndian)
        val blue = Vect.drop(16).take(8).toInt(false, LittleEndian)
        val colorNew = red * 1000000 + green * 1000 + blue 
        
        //format RRRGGGBBB
        
        crColorofTable(table :+ colorNew, size - 1, Vect.drop(24))
      }
    }
    
    def Drop(Vect: BitVect): BitVect = {
      
      val size = Vect.take(8).toInt(false, LittleEndian)
      val Vectnew = Vect.drop(8)
      
      if (size == 0)  Vectnew
      else  Drop(Vectnew.drop(8 * size))
      
    }
    
    def getImage(vec: BitVect, acc: BitVect): BitVect = {
      def reversebits(in_bl: BitVect, Obl: BitVect): BitVect = {
        if (in_bl.isEmpty) {
          Obl
        }
        else  reversebits(in_bl.drop(8), Obl ++ in_bl.take(8).reverseBitOrder)
      }
      
      val size = vec.take(8).toInt(false, LittleEndian)
      var Vect = vec.drop(8)
      
      if (size == 0)  acc
      
      else {
        val block = Vect.take(size * 8)
        getImage(Vect.drop(size * 8), acc ++ reversebits(block, BitVect(Nil)))
      }
    }

    def caseDescript(Vect: BitVect, giffile: giffile): giffile = {

      val Ext = Vect.take(8).toInt(false, LittleEndian)

      if (Ext == 44) {
        
        val imageDescriptNew = imageCodec.decode(Vect.drop(8)).require.value
        var LSTnew: Array[Int] = Array[Int]()
        var Vectnew = Vect.drop(8).drop(9 * 8)
        
        if (imageDescriptNew.LCT_flag) {
          LSTnew = crColorofTable(LSTnew, Math.pow(2, imageDescriptNew.LCT_size + 1).toInt, Vect)
          Vectnew = Vectnew.drop(Math.pow(2, imageDescriptNew.LCT_size + 1).toInt * 3 * 8)
        }
        val root = (Vectnew.take(8).toInt(false, LittleEndian))
        Vectnew = Vectnew.drop(8)
        var image_Vect = getImage(Vectnew, BitVect(Nil))
        var CT: Array[Int] = Array[Int]()
        
        if (imageDescriptNew.LCT_flag)  CT = LSTnew
       
        else  CT = giffile.globColorTable
        
        val imageNew = LZW(root + 1, image_Vect, CT.toList ::: List(1000000000, 2000000000))
        val gifNew = new giffile(giffile.header, giffile.globColorTable, imageDescriptNew ::
          giffile.imagedes, imageNew :: giffile.images,
          giffile.animations)
        Vectnew = Drop(Vectnew)
        caseDescript(Vectnew, gifNew)
      }
      else if (Ext == 59) {

        val gifOut = new giffile(giffile.header, giffile.globColorTable, giffile.imagedes.reverse, giffile.images.reverse, giffile.animations.reverse)
        gifOut
      }
      else if (Ext == 33) {

        val Labl = Vect.drop(8).take(8).toInt(false, LittleEndian)

        if (Labl == 249) {
          val new_animation = animationCodec.decode(Vect.drop(27)).require.value
          val gifNew = new giffile(giffile.header, giffile.globColorTable, giffile.imagedes,
            giffile.images, new_animation :: giffile.animations)
          caseDescript(Vect.drop(16).drop(6 * 8), gifNew)
        }
        else if (Labl == 254) {
          val Vectnew = Drop(Vect.drop(16))
          caseDescript(Vectnew, giffile)
        }
        else if (Labl == 1) {
          val Vectnew = Drop(Vect.drop(16).drop(13 * 8))
          caseDescript(Vectnew, giffile)
        }
        else if (Labl == 255) {
          val Vectnew = Drop(Vect.drop(16))
          caseDescript(Vectnew, giffile)
        }
        else {
          throw new NoSuchElementException()
        }
      }
      else {
        throw new NoSuchElementException()
      }
    }

    val byteArray = Files.readAllBytes(Paths.get(path))
    var bitVect = (BitVect(byteArray)).drop(48)
    val decoded_header = headerCodec.decode(bitVect).require.value
    bitVect = bitVect.drop(7 * 8)
    var GCT: Array[Int] = Array[Int](0)
    if (decoded_header.GCT_flag) {
      GCT = crColorofTable(Array[Int](), Math.pow(2, decoded_header.GCT_size + 1).toInt, bitVect)
      bitVect = bitVect.drop(Math.pow(2, decoded_header.GCT_size + 1).toInt * 3 * 8)
    }
    val file = new giffile(decoded_header, GCT, Nil, Nil, Nil)
    caseDescript(bitVect, file)
  }
  def color(col: Int): Color = {
    new Color(col / 1000000, (col / 1000) % 1000, col % 1000)
  }
  def getFrame(ims: List[Array[Int]], Dsc: List[image], acc: List[Array[Array[Color]]]): List[Array[Array[Color]]] = {
    def frame(Bk: Array[Array[Color]], im: Array[Int], w: Int, h: Int, desc: image): Array[Array[Color]] = {
      
      val new_frame = Bk
      var i = 0
      
      for {
        x <- 0 until w
        y <- 0 until h
      } {
        if (x >= desc.LP && y>= desc.TP) {
          new_frame(x)(y) = color(im(i))
          i = i + 1
        }
      }
      new_frame
    }
    if(ims.isEmpty)  acc
    
    else {
      getFrame(ims.tail, Dsc.tail, acc :+ frame(Array.fill(gif.header.width,
        gif.header.height)(color(gif.globColorTable(gif.header.Bkground_color))), ims.head,
        gif.header.width, gif.header.height, Dsc.head))
    }
  }
    
  val gif: giffile = Decode("file.gif")
  val scale = 30
  val Bk = Array.fill(gif.header.width, gif.header.height)(color(gif.globColorTable(gif.header.Bkground_color)))
    val module = frames.length
    val frames = getFrame(gif.images, gif.imagedes, Nil).toArray
  var Numb = 0
    
  def Peak = new MainFrame {
    def tick() = {
      
      var methodDisp= gif.animations(Numb % module).method
      
      if (methodDisp == 2) {
        contents = new DataPanel(Bk)
        {
          preferredSize = new Dimension(gif.header.width * scale , gif.header.height * scale)
        }
      }
      else if (methodDisp== 3) {
        contents = new argsPanel(frames((Numb - 1) % module)) {
          preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
        }
      }
      
      Numb = Numb + 1
      contents = new DataPanel(frames((Numb - 1) % module)) {
        preferredSize = new Dimension(gif.header.width * scale, gif.header.height * scale)
      }
    }

    Timer(gif.animations(Numb % module).detention) {tick()}

  }
}