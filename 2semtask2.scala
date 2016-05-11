/**
  * Created by Павел on 08.05.2016.
  */
object PascalsTriange {
  @annotation.tailrec
  def fact(n: Int, out: Int): Int =
    if (n <= 1)
      out
    else fact(n - 1, out * n)

  def FindElement(x: Int, y: Int): Int = {
    fact(x, 1) / (fact(x - y, 1)*fact(y, 1))
  }

  def main(Arg: Array[String]): Unit =
    println(FindElement(5, 3))
}

object CheckupBalance {
  def check1(L: List[Char]): Boolean = {
    @annotation.tailrec
    def check2(L: List[Char], i: Int): Boolean =
      if (L.isEmpty)
        i == 0
      else if (L.head == '(')
        check2(L.tail, i + 1)
      else if (L.head == ')')
        if (i == 0)
          false
        else check2(L.tail, i - 1)
      else check2(L.tail, i)
    check2(L, 0)
  }
  def main(args: Array[String]): Unit =
    println(check1("((check)))".toList))
}

object Coins {
  def countChange(money: Int, coins: List[Int]): Int =
  if (money == 0)
      1
    else if ((money < 0) || (coins.isEmpty))
      0
    else countChange(money, coins.tail) + countChange(money - coins.head, coins)

  def main(Arg: Array[String]): Unit =
    println(countChange(50, List(1,2,5,10)))
}


object Solutions {
  def sign(x: Double): Int =
    if (x < 0) -1 else if (x > 0) 1 else 0
  def findSolutions(L: Array[Double]): List[Double] =
    if (L.length == 3) {
      // Square
      val a: Double = L(0)
      val b: Double = L(1)
      val c: Double = L(2)
      val D: Double = b * b - 4 * a * c
      if (D > 0) {
        List((-b - math.sqrt(D)) / (2 * a),
          (-b + math.sqrt(D)) / (2 * a))
      } else if (D == 0) {
        List(-b / (2 * a))
      } else Nil
    } else if (L.length == 4) {
      //  Cube
      if (L(0) == 0) { // Warning . It's just a square .
        findSolutions(L.drop(1)) // ~ array.tail
      } else if (L(0) == 1) {
        val a: Double = L(1)
        val b: Double = L(2)
        val c: Double = L(3)
        val q: Double = (a * a - 3 * b) / 9
        val r: Double = (2 * a * a * a - 9 * a * b + 27 * c) / 54
        val r_2_min_q_3: Double = r * r - q * q * q

        if (r_2_min_q_3 < 0) { // 3 solutions
        val t: Double = math.acos(r / math.sqrt(q * q * q)) / 3
          val pi: Double = 2 * math.Pi / 3

          List(2 * math.sqrt(q) * math.cos(t) - a / 3,
            2 * math.sqrt(q) * math.cos(t + pi) - a / 3,
            2 * math.sqrt(q) * math.cos(t - pi) - a / 3)
        } else { // 1 or 2 solutions
        val A: Double = sign(r) *
            math.pow(math.abs(r) +
              math.sqrt(r_2_min_q_3), 1/3)
          val B: Double = if (A == 0) 0 else q / A

          val y = (A + B) - a / 3
          if (A == B && A != 0)
            List(y, -A - a / 3)
          else
            List(y)
        }
      } else {
        findSolutions(L.map(_ / L(0)).toArray)
      }
    } else {
      println("No")
      Nil
    }
  def main(args: Array[String]): Unit =
    println(findSolutions(Array(0, 1, -3, 2)))
}

object len {
  @annotation.tailrec
  def length(L: List[Int], out: Int = 0): Int =
    if (L.isEmpty)
      out
    else length(L.tail, out + 1)

  def main(Arg: Array[String]): Unit =
    println(length(List(1, 2, 3, -1, -2, 0)))
}

object addtoEnd {
  def add(L: List[Any], in: Any): List[Any] =
    if (L.isEmpty)
      in :: Nil
    else L.head :: add(L.tail, in)

  def main(Arg: Array[String]): Unit =
    println(add(List(1, 2, 3, -1, -2, 0), 5))
}

object reverse {
  @annotation.tailrec
  def rev(L: List[Any], out: List[Any] = Nil): List[Any] =
    if (L.isEmpty)
      out
    else rev(L.tail, L.head :: out)

  def main(Arg: Array[String]): Unit =
    println(rev(List(1, 2, 3, -1, -2, 0)))
}

object summator {
  @annotation.tailrec
  def sum(L: List[Int], out: Int = 0): Int =
    if (L.isEmpty)
      out
    else sum(L.tail, out + L.head)

  def main(Arg: Array[String]): Unit =
    println(sum(List(1, 2, 3, -1, -2, 0)))
}

object Filter1 {
  def filt1(L: List[Int]): List[Int] = {
    if (L.isEmpty)
      Nil
    else if (L.head > 1) // criterion
      L.head :: filt1(L.tail)
    else filt1(L.tail)
  }

  def main(Arg: Array[String]): Unit =
    println(filt1(List(1, 2, 3, -1, -2, 0)))
}

object Filter2 {
  def filt2(pred: Int => Boolean, L: List[Int]): List[Int] =
    if (L.isEmpty)
      Nil
    else if (pred(L.head))
      L.head :: filt2(pred, L.tail)
    else filt2(pred, L.tail)

  def func(x: Int): Boolean =
    (x > 1)

  def main(Arg: Array[String]): Unit =
    println(filt2(func , List(1, 2, 3, -1, -2, 0)))
}



