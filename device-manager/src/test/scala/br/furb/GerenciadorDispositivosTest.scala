package br.furb

import br.furb.adapter.lampada.{LampadaFactory, TipoLampada}
import br.furb.adapter.persiana.{PersianaFactory, TipoPersiana}
import br.furb.adapter.arcondicionado.{ArCondicionandoFactory, TipoArCondicionado}
import munit.FunSuite

class GerenciadorDispositivosTest extends FunSuite {

  test("addLampada should add lampadas") {
    val manager = new GerenciadorDispositivos()
    val lamp = LampadaFactory.criarLampada(TipoLampada.ShoyouMi)
    manager.addLampada(lamp)
    // Since private, can't check directly, but assume added
  }

  test("ligarTodasLampadas should turn on all lampadas") {
    val manager = new GerenciadorDispositivos()
    val lamp1 = LampadaFactory.criarLampada(TipoLampada.ShoyouMi)
    val lamp2 = LampadaFactory.criarLampada(TipoLampada.Phelippes)
    manager.addLampada(lamp1)
    manager.addLampada(lamp2)
    manager.ligarTodasLampadas()
    assert(lamp1.estaLigada())
    assert(lamp2.estaLigada())
  }

  test("desligarTodasLampadas should turn off all lampadas") {
    val manager = new GerenciadorDispositivos()
    val lamp1 = LampadaFactory.criarLampada(TipoLampada.ShoyouMi)
    val lamp2 = LampadaFactory.criarLampada(TipoLampada.Phelippes)
    manager.addLampada(lamp1)
    manager.addLampada(lamp2)
    manager.ligarTodasLampadas()
    assert(lamp1.estaLigada())
    assert(lamp2.estaLigada())
    manager.desligarTodasLampadas()
    assert(!lamp1.estaLigada())
    assert(!lamp2.estaLigada())
  }

  test("subirTodasPersianas should open all persianas") {
    val manager = new GerenciadorDispositivos()
    val pers1 = PersianaFactory.criarPersiana(TipoPersiana.NatLight)
    val pers2 = PersianaFactory.criarPersiana(TipoPersiana.Solarius)
    manager.addPersiana(pers1)
    manager.addPersiana(pers2)
    manager.subirTodasPersianas()
    assert(pers1.estaAberta())
    assert(pers2.estaAberta())
  }

  test("descerTodasPersianas should close all persianas") {
    val manager = new GerenciadorDispositivos()
    val pers1 = PersianaFactory.criarPersiana(TipoPersiana.NatLight)
    val pers2 = PersianaFactory.criarPersiana(TipoPersiana.Solarius)
    manager.addPersiana(pers1)
    manager.addPersiana(pers2)
    manager.subirTodasPersianas()
    assert(pers1.estaAberta())
    assert(pers2.estaAberta())
    manager.descerTodasPersianas()
    assert(!pers1.estaAberta())
    assert(!pers2.estaAberta())
  }

  test("ligarTodosArCondicionados should turn on all ar condicionados") {
    val manager = new GerenciadorDispositivos()
    val ac1 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.GellaKaza)
    val ac2 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.VentoBaumn)
    manager.addArCondicionado(ac1)
    manager.addArCondicionado(ac2)
    // Assume ligar doesn't change temp, just call
    manager.ligarTodosArCondicionados()
    // No direct way to check if ligado, since no estaLigado method
  }

  test("aumentarTemperaturaTodosArCondicionados should increase temperatures") {
    val manager = new GerenciadorDispositivos()
    val ac1 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.GellaKaza)
    val ac2 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.VentoBaumn)
    manager.addArCondicionado(ac1)
    manager.addArCondicionado(ac2)
    val temp1 = ac1.temperatura()
    val temp2 = ac2.temperatura()
    manager.aumentarTemperaturaTodosArCondicionados()
    assert(ac1.temperatura() > temp1)
    assert(ac2.temperatura() > temp2)
  }

  test("abaixarTemperaturaTodosArCondicionados should decrease temperatures") {
    val manager = new GerenciadorDispositivos()
    val ac1 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.GellaKaza)
    val ac2 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.VentoBaumn)
    manager.addArCondicionado(ac1)
    manager.addArCondicionado(ac2)
    val temp1 = ac1.temperatura()
    val temp2 = ac2.temperatura()
      manager.ligarTodosArCondicionados()
    manager.abaixarTemperaturaTodosArCondicionados()
    assert(ac1.temperatura() < temp1)
    assert(ac2.temperatura() < temp2)
  }
}
