package br.furb.adapter.arcondicionado

import munit.FunSuite

class ArCondicionadoVentoBaumnTest extends FunSuite {

  test("ArCondicionadoVentoBaumn should allow ligar and desligar without error") {
    val ac = new ArCondicionadoVentoBaumn()
    ac.ligar()
    ac.desligar()
  }

  test("aumentarTemperatura should increase temperature") {
    val ac = new ArCondicionadoVentoBaumn()
    val initialTemp = ac.temperatura()
      ac.ligar()
    ac.aumentarTemperatura()
    assert(ac.temperatura() > initialTemp)
  }

  test("abaixarTemperatura should decrease temperature") {
    val ac = new ArCondicionadoVentoBaumn()
    val initialTemp = ac.temperatura()
      ac.ligar()
    ac.abaixarTemperatura()
    assert(ac.temperatura() < initialTemp)
  }
}
