package br.furb.adapter.lampada

import munit.FunSuite

class LampadaFactoryTest extends FunSuite {

  test("criarLampada should create LampadaShoyouMi for TipoLampada.ShoyouMi") {
    val lampada = LampadaFactory.criarLampada(TipoLampada.ShoyouMi)
    assert(lampada.isInstanceOf[LampadaShoyouMi])
  }

  test("criarLampada should create LampadaPhelippes for TipoLampada.Phelippes") {
    val lampada = LampadaFactory.criarLampada(TipoLampada.Phelippes)
    assert(lampada.isInstanceOf[LampadaPhelippes])
  }

  test("criarLampada should throw NullPointerException for null") {
    intercept[NullPointerException] {
      LampadaFactory.criarLampada(null)
    }
  }
}
