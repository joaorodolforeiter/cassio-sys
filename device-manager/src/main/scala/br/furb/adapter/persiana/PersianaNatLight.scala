package br.furb.adapter.persiana

class PersianaNatLight extends Persiana {
    private val persiana = new br.furb.analise.algoritmos.PersianaNatLight()

    override def subir(): Unit = {
        persiana.abrirPalheta()
        persiana.subirPalheta()
    }

    override def descer(): Unit = {
        persiana.descerPalheta()
        persiana.fecharPalheta()
    }
}
