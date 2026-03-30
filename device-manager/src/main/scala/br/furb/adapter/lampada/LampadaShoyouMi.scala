package br.furb.adapter.lampada

class LampadaShoyouMi extends Lampada {
    private val lampada = new br.furb.analise.algoritmos.LampadaShoyuMi()

    override def ligar(): Unit = {
        lampada.ligar()
    }

    override def desligar(): Unit = {
        lampada.desligar()
    }
    
    override def estaLigada(): Boolean = {
        lampada.estaLigada()
    }
}
