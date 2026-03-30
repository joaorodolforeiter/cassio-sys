package br.furb

import br.furb.adapter.lampada._
import br.furb.adapter.persiana._
import br.furb.adapter.arcondicionado._
import scala.collection.mutable.ListBuffer

class GerenciadorDispositivos {
    private val lampadas = ListBuffer[Lampada]()
    private val persianas = ListBuffer[Persiana]()
    private val arCondicionados = ListBuffer[ArCondicionado]()

    def addLampada(lampada: Lampada): Unit = lampadas += lampada

    def addPersiana(persiana: Persiana): Unit = persianas += persiana

    def addArCondicionado(arCondicionado: ArCondicionado): Unit = arCondicionados += arCondicionado

    def ligarTodasLampadas(): Unit = {
        lampadas.foreach(_.ligar())
        println("Todas as lâmpadas foram ligadas.")
    }

    def desligarTodasLampadas(): Unit = {
        lampadas.foreach(_.desligar())
        println("Todas as lâmpadas foram desligadas.")
    }

    def subirTodasPersianas(): Unit = {
        persianas.foreach(_.subir())
        println("Todas as persianas foram subidas.")
    }

    def descerTodasPersianas(): Unit = {
        persianas.foreach(_.descer())
        println("Todas as persianas foram descidas.")
    }

    def ligarTodosArCondicionados(): Unit = {
        arCondicionados.foreach(_.ligar())
        println("Todos os ar-condicionados foram ligados.")
        imprimirTemperaturas()
    }

    def desligarTodosArCondicionados(): Unit = {
        arCondicionados.foreach(_.desligar())
        println("Todos os ar-condicionados foram desligados.")
    }

    def aumentarTemperaturaTodosArCondicionados(): Unit = {
        arCondicionados.foreach(_.ligar())
        arCondicionados.foreach(_.aumentarTemperatura())
        println("Temperatura aumentada em todos os ar-condicionados.")
        imprimirTemperaturas()
    }

    def abaixarTemperaturaTodosArCondicionados(): Unit = {
        arCondicionados.foreach(_.abaixarTemperatura())
        println("Temperatura abaixada em todos os ar-condicionados.")
        imprimirTemperaturas()
    }

    def imprimirTemperaturas(): Unit = {
        arCondicionados.zipWithIndex.foreach { case (ac, i) =>
            println(s"Ar Condicionado ${i + 1}: ${ac.temperatura()}°C")
        }
    }
}
