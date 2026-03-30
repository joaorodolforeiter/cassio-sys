package br.furb.adapter.lampada

trait Lampada {
    def ligar(): Unit
    def desligar(): Unit
    def estaLigada(): Boolean
}
