package br.furb.adapter.persiana

import munit.FunSuite

class PersianaNatLightTest extends FunSuite {

  test("PersianaNatLight should start open") {
    val persiana = new PersianaNatLight()
    assert(persiana.estaAberta())
  }

  test("subir should open the persiana") {
    val persiana = new PersianaNatLight()
    persiana.subir()
    assert(persiana.estaAberta())
  }

  test("descer should close the persiana") {
    val persiana = new PersianaNatLight()
    persiana.subir()
    assert(persiana.estaAberta())
    persiana.descer()
    assert(!persiana.estaAberta())
  }
}
