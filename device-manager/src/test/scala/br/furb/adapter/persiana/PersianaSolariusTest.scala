package br.furb.adapter.persiana

import munit.FunSuite

class PersianaSolariusTest extends FunSuite {

    test("PersianaSolarius should start open") {
        val persiana = new PersianaSolarius()
        assert(persiana.estaAberta())
    }

    test("subir should open the persiana") {
        val persiana = new PersianaSolarius()
        persiana.subir()
        assert(persiana.estaAberta())
    }

    test("descer should close the persiana") {
        val persiana = new PersianaSolarius()
        persiana.subir()
        assert(persiana.estaAberta())
        persiana.descer()
        assert(!persiana.estaAberta())
    }
}
