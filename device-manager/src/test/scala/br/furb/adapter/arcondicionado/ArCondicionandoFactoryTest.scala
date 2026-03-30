package br.furb.adapter.arcondicionado

import munit.FunSuite

class ArCondicionandoFactoryTest extends FunSuite {

  test("criarArCondicionado should create ArCondicionadoGellaKaza for TipoArCondicionado.GellaKaza") {
    val ac = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.GellaKaza)
    assert(ac.isInstanceOf[ArCondicionadoGellaKaza])
  }

  test("criarArCondicionado should create ArCondicionadoVentoBaumn for TipoArCondicionado.VentoBaumn") {
    val ac = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.VentoBaumn)
    assert(ac.isInstanceOf[ArCondicionadoVentoBaumn])
  }

  test("criarArCondicionado should throw NullPointerException for null") {
    intercept[NullPointerException] {
      ArCondicionandoFactory.criarArCondicionado(null)
    }
  }
}
