
object allocation {

  abstract class ParagraphElement {
    override def toString: String
    def length: Int
  }

  case class Word(val L: String) extends ParagraphElement {
    override def toString: String =
      "Word(" + this.L + ")"
    def length: Int = L.length
  }

  case class Space(val length: Int) extends ParagraphElement {
    override def toString: String =
      "Space(" + this.length.toString + ")"
  }

  def main(A: Array[String]) {
    def Test (words: List[String], screen: Int, align: String): List[List[ParagraphElement]] = {
      def сontrol (L: List[String], width: Int):List[String] = {
        if (L.isEmpty) Nil
        else {
          val E = L.head
          val len: Int = E.length()
          require(len <= screen, "Error - too long")
          if (len <= width){
            if (width-len == 0){
              E::Nil
            }
            else E :: сontrol(L.tail, width - len - 1)
          }
          else Nil
        }
      }

      def all (list1: List[String]):List[List[String]] = {
        if (list1.isEmpty) Nil
        else {
          val x = сontrol(list1, screen)
          x::all(list1 drop x.length)
        }
      }

      def allalign (x: List[String] => List[ParagraphElement],l:List[List[String]]): List[List[ParagraphElement]] = {
        if (l.isEmpty) Nil
        else x(l.head)::allalign(x,l.tail)
      }

      def case1 (list2: List[String]): List[ParagraphElement] = {
        if (list2.tail.isEmpty) new Word(list2.head):: Nil
        else (new Word(list2.head)::new Space(1)::case1(list2.tail))
      }

      def case2 (list2: List[String], amount: Int): List[ParagraphElement] = {
        if (list2.tail.isEmpty) new Word(list2.head)::new Space(amount):: Nil
        else (new Word(list2.head)::new Space(1)::case2(list2.tail, amount))
      }
      def number (L : List[String]): Int = {
        if (L.isEmpty)
          0
        else
          L.head.length + number(L.tail)
      }

      def right (L: List[String]): List[ParagraphElement] = {
        val amount = screen - number(L) - L.length + 1
        if (amount == 0) case1(L)
        else (new Space(amount) :: case1(L))
      }

      def left (L: List[String]): List[ParagraphElement] = {
        val amount = screen - number(L) - L.length + 1
        if (amount == 0) case1(L)
        else case2(L, amount)
      }
      def centre (L: List[String]): List[ParagraphElement] = {
        val amount: Int = screen - number(L) - L.length + 1
        if (amount == 0) case1(L)
        else new Space(amount/2) :: case2(L, (amount - amount / 2))
      }

      def fit (L: List[String]): List[ParagraphElement] = {
        val amount = screen  - number(L) - L.length + 1
        val st: Int = amount / (L.length - 1)
        val lt : Int = amount % (L.length - 1)

        def Fit (list: List[String]): List[ParagraphElement] = {
          if (list.tail.length == 2) (new Word(list.head)::new Space(st+lt) :: new Word(list.tail.head):: Nil)
          else (new Word(list.head)::new Space(st+1):: Fit(list.tail))
        }

        if (amount == 0) case1(L)
        else Fit(L)

      }
      if (align == "r")
        allalign(right, all(words))
      else
      if (align == "l")
        allalign(left, all(words))
      else
      if (align == "f")
        allalign(fit, all(words))
      else
      if (align == "c")
        allalign(centre, all(words))
      else Nil
    }

    val x = Test (List("His","H","He", "H"), 7, "l")
    def pr(l : List[List[ParagraphElement]]): Unit = {
      if (l.isEmpty) Nil
      else println(l.head +" "+ pr(l.tail))
    }

    pr(x)

  }
}






















