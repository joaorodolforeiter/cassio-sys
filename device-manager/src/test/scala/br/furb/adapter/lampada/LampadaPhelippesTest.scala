package br.furb.adapter.lampada

import munit.FunSuite

class LampadaPhelippesTest extends FunSuite {

  test("LampadaPhelippes should start off") {
    val lampada = new LampadaPhelippes()
    assert(!lampada.estaLigada())
  }

  test("ligar should turn on the lampada") {
    val lampada = new LampadaPhelippes()
    lampada.ligar()
    assert(lampada.estaLigada())
  }

  test("desligar should turn off the lampada") {
    val lampada = new LampadaPhelippes()
    lampada.ligar()
    assert(lampada.estaLigada())
    lampada.desligar()
    assert(!lampada.estaLigada())
  }
}
