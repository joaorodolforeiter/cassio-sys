package br.furb.adapter.arcondicionado

import munit.FunSuite

class ArCondicionadoGellaKazaTest extends FunSuite {

  test("ArCondicionadoGellaKaza should allow ligar and desligar without error") {
    val ac = new ArCondicionadoGellaKaza()
    ac.ligar()
    ac.desligar()
  }

  test("aumentarTemperatura should increase temperature") {
    val ac = new ArCondicionadoGellaKaza()
    val initialTemp = ac.temperatura()
    ac.aumentarTemperatura()
    assert(ac.temperatura() > initialTemp)
  }

  test("abaixarTemperatura should decrease temperature") {
    val ac = new ArCondicionadoGellaKaza()
    val initialTemp = ac.temperatura()
    ac.abaixarTemperatura()
    assert(ac.temperatura() < initialTemp)
  }
}
