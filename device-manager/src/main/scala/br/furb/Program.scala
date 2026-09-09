package br.furb

import br.furb.adapter.lampada.{LampadaFactory, TipoLampada}
import br.furb.adapter.persiana.{PersianaFactory, TipoPersiana}
import br.furb.adapter.arcondicionado.{ArCondicionandoFactory, TipoArCondicionado}

@main
def main(): Unit = {
  val manager = new GerenciadorDispositivos()

  // Criar e adicionar lâmpadas
  val lamp1 = LampadaFactory.criarLampada(TipoLampada.ShoyouMi)
  val lamp2 = LampadaFactory.criarLampada(TipoLampada.Phelippes)
  manager.addLampada(lamp1)
  manager.addLampada(lamp2)

  // Criar e adicionar persianas
  val pers1 = PersianaFactory.criarPersiana(TipoPersiana.Solarius)
  val pers2 = PersianaFactory.criarPersiana(TipoPersiana.NatLight)
  manager.addPersiana(pers1)
  manager.addPersiana(pers2)

  // Criar e adicionar ar-condicionados
  val ac1 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.VentoBaumn)
  val ac2 = ArCondicionandoFactory.criarArCondicionado(TipoArCondicionado.GellaKaza)
  manager.addArCondicionado(ac1)
  manager.addArCondicionado(ac2)

  // Demonstrar controle
  println("=== Demonstrando controle de dispositivos IoT ===")
  println("\nLigando todas as lâmpadas...")
  manager.ligarTodasLampadas()
  println("\nSubindo todas as persianas...")
  manager.subirTodasPersianas()
  println("\nLigando todos os ar-condicionados...")
  manager.ligarTodosArCondicionados()
  println("\nAumentando temperatura de todos os ar-condicionados...")
  manager.aumentarTemperaturaTodosArCondicionados()
  println("\nAumentando novamente...")
  manager.aumentarTemperaturaTodosArCondicionados()
  println("\nDescendo todas as persianas...")
  manager.descerTodasPersianas()
  println("\nDesligando todas as lâmpadas...")
  manager.desligarTodasLampadas()
  println("\nDesligando todos os ar-condicionados...")
  manager.desligarTodosArCondicionados()
  println("\n=== Fim da demonstração ===")
}
