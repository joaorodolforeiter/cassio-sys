package br.furb.adapter.lampada

class LampadaPhelippes extends Lampada {
    private val lampada = new br.furb.analise.algoritmos.LampadaPhellipes()

    override def ligar(): Unit = {
        lampada.setIntensidade(100)
    }

    override def desligar(): Unit = {
        lampada.setIntensidade(0)
    }
    
    override def estaLigada(): Boolean = {
        lampada.getIntensidade > 0
    }
}
