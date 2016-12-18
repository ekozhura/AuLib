/////////////////////////////////////////////////////////////////////
// Comb class: Comb filter
// Copyright (C) 2016-7 V Lazzarini
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _COMB_H_
#define _COMB_H_
#include "Delay.h"

namespace AuLib {

  /** Comb filter
   */
  class Comb : public Delay {

  protected:
    double m_fdb;

    /** filter kernel
     */
    virtual const double* filter(const double* sig, double fdb);
  
  public:
    /** Comb constructor \n\n
	dtime - delay time \n
        fdb - feedback gain \n
	vframes - vector size \n
        sr - sampling rate
    */  
    Comb(double dtime, double fdb,
	 uint32_t vframes = def_vframes,
	 double sr = def_sr) :
      m_fdb(fdb), 
      Delay(dtime,vframes,sr) { };

    /** process a signal sig 
     */
    virtual const double* process(const double* sig, double fdb = -1.){
      return filter(sig, fdb);
    }

    /** process a signal in obj
     */
    virtual const Comb& process(const AudioBase& obj, double fdb = -1.) {
      if(obj.vframes() == m_vframes &&
	 obj.nchnls() == m_nchnls) {
	process(obj.vector(),fdb);
      } else m_error = AULIB_ERROR;
      return *this;
    }
    
  };

  /*! \class Comb Comb.h AuLib/Comb.h
   */

}
#endif
