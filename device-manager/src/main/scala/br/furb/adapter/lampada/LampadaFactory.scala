package br.furb.adapter.lampada

object LampadaFactory {
    def criarLampada(tipoLampada: TipoLampada): Lampada = {
        tipoLampada match {
            case null => throw new NullPointerException("tipoLampada não pode ser nulo")
            case TipoLampada.ShoyouMi => new LampadaShoyouMi()
            case TipoLampada.Phelippes => new LampadaPhelippes()
        }
    }
}
