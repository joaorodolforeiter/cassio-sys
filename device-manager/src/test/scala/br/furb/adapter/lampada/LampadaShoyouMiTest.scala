package br.furb.adapter.lampada

import munit.FunSuite

class LampadaShoyouMiTest extends FunSuite {

  test("LampadaShoyouMi should start off") {
    val lampada = new LampadaShoyouMi()
    assert(!lampada.estaLigada())
  }

  test("ligar should turn on the lampada") {
    val lampada = new LampadaShoyouMi()
    lampada.ligar()
    assert(lampada.estaLigada())
  }

  test("desligar should turn off the lampada") {
    val lampada = new LampadaShoyouMi()
    lampada.ligar()
    assert(lampada.estaLigada())
    lampada.desligar()
    assert(!lampada.estaLigada())
  }
}
