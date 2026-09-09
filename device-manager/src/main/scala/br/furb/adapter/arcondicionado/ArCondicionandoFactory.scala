package br.furb.adapter.arcondicionado



object ArCondicionandoFactory {
  def criarArCondicionado(tipoArCondicionado: TipoArCondicionado): ArCondicionado = {
    tipoArCondicionado match {
      case null => throw new NullPointerException("tipoArCondicionado não posso ser nulo")
      case TipoArCondicionado.GellaKaza => new ArCondicionadoGellaKaza()
      case TipoArCondicionado.VentoBaumn => new ArCondicionadoVentoBaumn()
    }
  }
}
