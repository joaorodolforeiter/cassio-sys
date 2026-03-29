package br.furb.adapter.arcondicionado


class ArCondicionadoGellaKaza extends ArCondicionado {
  private val arCondicionado = new br.furb.analise.algoritmos.ArCondicionadoGellaKaza();

  override def ligar(): Unit = arCondicionado.ativar()

  override def desligar(): Unit = arCondicionado.desativar()

  override def aumentarTemperatura(): Unit = arCondicionado.aumentarTemperatura()

  override def abaixarTemperatura(): Unit = arCondicionado.diminuirTemperatura()

  override def temperatura(): Int = arCondicionado.getTemperatura
}