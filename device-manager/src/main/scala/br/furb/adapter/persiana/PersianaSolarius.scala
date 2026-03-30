package br.furb.adapter.persiana

class PersianaSolarius extends Persiana {
    private val persiana = new br.furb.analise.algoritmos.PersianaSolarius()

    override def subir(): Unit = {
        persiana.subirPersiana()
    }

    override def descer(): Unit = {
        persiana.descerPersiana()
    }
}
