////////////////////////////////////////////////////////////////////
// Implementation of the Delay and derived classes
// Copyright (C) 2016-7 V Lazzarini
//
// This software is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Delay.h"
#include "Comb.h"
#include "AllPass.h"

const double*
AuLib::Delay::process(const double* sig){
  for(int i = 0; i < m_vframes; i++) {
    m_vector[i] = m_delay.set(sig[i], m_pos);
    m_pos = m_pos == m_delay.vframes()-1 ? 0. : m_pos+1;
  }
  return vector();
}


const double*
AuLib::Comb::filter(const double* sig, double fdb){
  if(fdb >= 0.) m_fdb = fdb;
  double y;
  for(int i = 0; i < m_vframes; i++) {
    y = sig[i] + m_fdb*m_delay.vector(m_pos);
    m_vector[i] = m_delay.set(y,m_pos);
    m_pos = m_pos == m_delay.vframes()-1 ? 0. : m_pos+1;
  }
  return vector();
}

const double*
AuLib::AllPass::filter(const double* sig, double fdb){
  if(fdb >= 0.) m_fdb = fdb;
  double y;
  for(int i = 0; i < m_vframes; i++) {
    y = sig[i] + m_fdb*m_delay.vector(m_pos);
    m_vector[i] = m_delay.set(y, m_pos) - m_fdb*y;
    m_pos = m_pos == m_delay.vframes()-1 ? 0. : m_pos+1;
  }
  return vector();
}



