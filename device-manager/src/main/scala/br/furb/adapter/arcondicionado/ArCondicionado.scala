package br.furb.adapter.arcondicionado

trait ArCondicionado {
    def ligar(): Unit;
    def desligar(): Unit;
    def aumentarTemperatura(): Unit;
    def abaixarTemperatura(): Unit;
    def temperatura(): Int;
}
