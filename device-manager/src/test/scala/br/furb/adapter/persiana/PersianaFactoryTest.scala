package br.furb.adapter.persiana

import munit.FunSuite

class PersianaFactoryTest extends FunSuite {

  test("criarPersiana should create PersianaNatLight for TipoPersiana.NatLight") {
    val persiana = PersianaFactory.criarPersiana(TipoPersiana.NatLight)
    assert(persiana.isInstanceOf[PersianaNatLight])
  }

  test("criarPersiana should create PersianaSolarius for TipoPersiana.Solarius") {
    val persiana = PersianaFactory.criarPersiana(TipoPersiana.Solarius)
    assert(persiana.isInstanceOf[PersianaSolarius])
  }

  test("criarPersiana should throw NullPointerException for null") {
    intercept[NullPointerException] {
      PersianaFactory.criarPersiana(null)
    }
  }
}
