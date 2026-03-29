package br.furb.adapter.arcondicionado

import br.furb.analise.algoritmos

class ArCondicionadoVentoBaumn extends ArCondicionado {
    private val arCondicionado = new algoritmos.ArCondicionadoVentoBaumn();

    override def ligar(): Unit = arCondicionado.ligar()

    override def desligar(): Unit = arCondicionado.desligar()

    override def aumentarTemperatura(): Unit = arCondicionado.definirTemperatura(temperatura() + 1)

    override def abaixarTemperatura(): Unit = arCondicionado.definirTemperatura(temperatura() - 1)

    override def temperatura(): Int = arCondicionado.getTemperatura

}