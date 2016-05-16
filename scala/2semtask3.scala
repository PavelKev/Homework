/**
  * Created by Павел on 14.05.2016.
  */
object SetRealisation {
  type Set = Int => Boolean

  def contains(s: Set, elem: Int): Boolean =
    s(elem)

  def singletonSet(elem: Int): Set =
    x => x == elem

  def union(s: Set, t: Set): Set =
    x => contains(s, x) || contains(t, x)

  def intersect(s: Set, t: Set): Set =
    x => contains(s, x) && contains(t, x)

  def diff(s: Set, t: Set): Set =
    x => contains(s, x) && !contains(t, x)

  def filter(s: Set, p: Int => Boolean): Set =
    x => contains(s, x) && p(x)

  def forall(s: Set, p: Int => Boolean): Boolean = {
    val bound = 1000
    @annotation.tailrec
    def iter(x: Int): Boolean =
      if (x > bound)
        true
      else if (contains(s, x) && !p(x))
        false
      else iter(x + 1)
    iter(-bound)
  }

  def getall(s: Set): String = {
    val bound = 1000
    def toString(s: Set): String = {
      val xs = for (i <- -bound to bound if contains(s, i)) yield i
      xs.mkString("{", ",", "}")
    }
    toString(s)
  }

  def exists(s: Set, p: Int => Boolean): Boolean = {
    val bound = 1000
    @annotation.tailrec
    def iter(x: Int): Boolean =
      if (x > bound)
        false
      else if (contains(s, x) && p(x))
        true
      else iter(x + 1)
    iter(-bound)
  }

  def map(s: Set, f: Int => Int): Set = {
    val bound = 1000

    def iter(x: Int): Set = {
      if (x > bound)
        x => false // empty
      else if (contains(s, x))
        union(singletonSet(f(x)), iter(x + 1))
      else iter(x + 1)
    }
    iter(-bound)
  }
}


