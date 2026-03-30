package br.furb.adapter.persiana

object PersianaFactory {
    
    def criarPersiana(tipoPersiana: TipoPersiana): Persiana = {
        tipoPersiana match {
            case null => throw new NullPointerException("tipoPersiana não pode ser nulo")
            case TipoPersiana.NatLight => new PersianaNatLight()
            case TipoPersiana.Solarius => new PersianaSolarius()
        }
    }
}
