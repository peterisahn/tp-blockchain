#include <iostream>

#include "calendario.h"
#include "blockchain.h"
#include "billetera.h"

using namespace std;

// DATOS
// billetera es individual y contiene el id y un puntero a la blockchain
// _billeteras es un map, que asocia un id con la billetera

// _transaccion contiene los datos de una transacción realizada: origen, destino, monto, tiempo actual
// _transacciones es una cadena de transaccion

Blockchain::Blockchain() {
  _transacciones = {};
  _billeteras = {};

  // sumo 1 porque el id 0 está reservado para las transacciones de saldo
  // inicial.
  _siguiente_id_billetera = static_cast<unsigned int>(rand()) + 1;
}

Billetera* Blockchain::abrir_billetera() {
  Billetera * billetera = new Billetera(_siguiente_id_billetera, this);
  _billeteras[billetera->id()] = billetera;
  _siguiente_id_billetera++;

  Transaccion transaccion = {0, billetera->id(), SALDO_INICIAL, Calendario::tiempo_actual()};
  _transacciones.push_back(transaccion);
  billetera->notificar_transaccion(transaccion);

  return billetera;
}

bool Blockchain::agregar_transaccion(Billetera* origen, id_billetera destino, double monto) {
  auto origen_it = _billeteras.find(origen->id());
  auto destino_it = _billeteras.find(destino);

  bool billeteras_distintas = origen->id() != destino;
  bool origen_valido = origen_it != _billeteras.end() && origen_it->second == origen;
  bool destino_valido = destino_it != _billeteras.end();
  bool saldo_suficiente = calcular_saldo(origen) >= monto;

  bool transaccion_aprobada = billeteras_distintas && origen_valido && destino_valido && saldo_suficiente;

  if (!transaccion_aprobada) {
    return false;
  }

  Transaccion transaccion = {origen->id(), destino, monto, Calendario::tiempo_actual()};

  _transacciones.push_back(transaccion);
  origen_it->second->notificar_transaccion(transaccion);
  destino_it->second->notificar_transaccion(transaccion);

  return true;
}

const list<Transaccion>& Blockchain::transacciones() {
  return _transacciones;
}

monto Blockchain::calcular_saldo(const Billetera* billetera) const {
  monto resultado = 0;

  for (auto it = _transacciones.begin(); it != _transacciones.end(); ++it) {
    Transaccion tx = *it;
    if (tx.origen == billetera->id()) {
      resultado -= tx.monto;
    } else if (tx.destino == billetera->id()) {
      resultado += tx.monto;
    }
  }

  return resultado;
}

Blockchain::~Blockchain() {
  auto it = this->_billeteras.begin();
  while (it != this->_billeteras.end()) {
    delete it->second;
    ++it;
  }
}
