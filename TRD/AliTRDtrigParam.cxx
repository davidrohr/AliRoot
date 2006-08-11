/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                                                           //
//  TRD trigger parameters class                                             //
//                                                                           //
//  Author:                                                                  //
//     Bogdan Vulpescu                                                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "AliTRDgeometry.h"

#include "AliTRDtrigParam.h"

ClassImp(AliTRDtrigParam)

//_____________________________________________________________________________
AliTRDtrigParam::AliTRDtrigParam()
  :TNamed()
  ,fDebug(0)
  ,fTime1(0)
  ,fTime2(0)
  ,fClusThr(0)
  ,fPadThr(0)
  ,fSum10(0)
  ,fSum12(0)
  ,fTCOn(0)
  ,fTCnexp(0)
  ,fFilterType(0)
  ,fR1(0)
  ,fR2(0)
  ,fC1(0)
  ,fC2(0)
  ,fPedestal(0)
  ,fADCnoise(0)
  ,fDeltaY(0)
  ,fDeltaS(0)
  ,fXprojPlane(0)
  ,fLtuPtCut(0)
  ,fGtuPtCut(0)
  ,fField(0)
  ,fHighPt(0)
  ,fNPartJetLow(0)
  ,fNPartJetHigh(0)
  ,fJetLowPt(0)
  ,fJetHighPt(0)
{
  //
  // AliTRDtrigParam default constructor
  //

}

//_____________________________________________________________________________
AliTRDtrigParam::AliTRDtrigParam(const Text_t *name, const Text_t *title)
  :TNamed(name,title)
  ,fDebug(0)
  ,fTime1(2)
  ,fTime2(22)
  ,fClusThr(10.0)
  ,fPadThr(1)
  ,fSum10(2)
  ,fSum12(10)
  ,fTCOn(1)
  ,fTCnexp(1)
  ,fFilterType(0)
  ,fR1(0)
  ,fR2(0)
  ,fC1(0)
  ,fC2(0)
  ,fPedestal(0)
  ,fADCnoise(0)
  ,fDeltaY(2.0)
  ,fDeltaS(2.5)
  ,fXprojPlane(0)
  ,fLtuPtCut(2.3)
  ,fGtuPtCut(3.0)
  ,fField(0)
  ,fHighPt(10.0)
  ,fNPartJetLow(5)
  ,fNPartJetHigh(3)
  ,fJetLowPt(3.0)
  ,fJetHighPt(5.0)
{
  //
  // AliTRDtrigParam constructor
  //

  // PASA.v.4
  if      (fTCnexp == 1) {
    fR1 = 1.1563;
    fR2 = 0.1299;
    fC1 = 0.0657;
    fC2 = 0.0000;
  }
  else if (fTCnexp == 2) {
    fR1 = 1.1563;
    fR2 = 0.1299;
    fC1 = 0.1141;
    fC2 = 0.6241;
  }

}

//_____________________________________________________________________________
AliTRDtrigParam::AliTRDtrigParam(const AliTRDtrigParam &p)
  :TNamed(p)
  ,fDebug(p.fDebug)
  ,fTime1(p.fTime1)
  ,fTime2(p.fTime2)
  ,fClusThr(p.fClusThr)
  ,fPadThr(p.fPadThr)
  ,fSum10(p.fSum10)
  ,fSum12(p.fSum12)
  ,fTCOn(p.fTCOn)
  ,fTCnexp(p.fTCnexp)
  ,fFilterType(p.fFilterType)
  ,fR1(p.fR1)
  ,fR2(p.fR2)
  ,fC1(p.fC1)
  ,fC2(p.fC2)
  ,fPedestal(p.fPedestal)
  ,fADCnoise(p.fADCnoise)
  ,fDeltaY(p.fDeltaY)
  ,fDeltaS(p.fDeltaS)
  ,fXprojPlane(p.fXprojPlane)
  ,fLtuPtCut(p.fLtuPtCut)
  ,fGtuPtCut(p.fGtuPtCut)
  ,fField(p.fField)
  ,fHighPt(p.fHighPt)
  ,fNPartJetLow(p.fNPartJetLow)
  ,fNPartJetHigh(p.fNPartJetHigh)
  ,fJetLowPt(p.fJetLowPt)
  ,fJetHighPt(p.fJetHighPt)
{
  //
  // AliTRDtrigParam copy constructor
  //

}

//_____________________________________________________________________________
AliTRDtrigParam::~AliTRDtrigParam()
{
  //
  // AliTRDtrigParam destructor
  //

}

//_____________________________________________________________________________
AliTRDtrigParam &AliTRDtrigParam::operator=(const AliTRDtrigParam &p)
{
  //
  // Assignment operator
  //

  if (this != &p) ((AliTRDtrigParam &) p).Copy(*this);
  return *this;

}

//_____________________________________________________________________________
void AliTRDtrigParam::Copy(TObject &p) const
{
  //
  // Copy function
  //

  ((AliTRDtrigParam &) p).fDebug        = fDebug;
  ((AliTRDtrigParam &) p).fTime1        = fTime1;
  ((AliTRDtrigParam &) p).fTime2        = fTime2;
  ((AliTRDtrigParam &) p).fClusThr      = fClusThr;
  ((AliTRDtrigParam &) p).fPadThr       = fPadThr;
  ((AliTRDtrigParam &) p).fSum10        = fSum10;
  ((AliTRDtrigParam &) p).fSum12        = fSum12;
  ((AliTRDtrigParam &) p).fTCOn         = fTCOn;
  ((AliTRDtrigParam &) p).fTCnexp       = fTCnexp;
  ((AliTRDtrigParam &) p).fFilterType   = fFilterType;
  ((AliTRDtrigParam &) p).fR1           = fR1;
  ((AliTRDtrigParam &) p).fR2           = fR2;
  ((AliTRDtrigParam &) p).fC1           = fC1;
  ((AliTRDtrigParam &) p).fC2           = fC2;
  ((AliTRDtrigParam &) p).fPedestal     = fPedestal;
  ((AliTRDtrigParam &) p).fADCnoise     = fADCnoise;
  ((AliTRDtrigParam &) p).fDeltaY       = fDeltaY;
  ((AliTRDtrigParam &) p).fDeltaS       = fDeltaS;
  ((AliTRDtrigParam &) p).fXprojPlane   = fXprojPlane;
  ((AliTRDtrigParam &) p).fField        = fField;
  ((AliTRDtrigParam &) p).fLtuPtCut     = fLtuPtCut;
  ((AliTRDtrigParam &) p).fGtuPtCut     = fGtuPtCut;
  ((AliTRDtrigParam &) p).fHighPt       = fHighPt;
  ((AliTRDtrigParam &) p).fNPartJetLow  = fNPartJetLow;
  ((AliTRDtrigParam &) p).fNPartJetHigh = fNPartJetHigh;
  ((AliTRDtrigParam &) p).fJetLowPt     = fJetLowPt;
  ((AliTRDtrigParam &) p).fJetHighPt    = fJetHighPt;

}

//_____________________________________________________________________________
void AliTRDtrigParam::Init()
{
  //
  // Initialize the other parameters
  //

  Float_t xPlane0;
  Float_t xPlane5;
 
  xPlane0     = AliTRDgeometry::GetTime0(0) 
              - AliTRDgeometry::CdrHght() 
              - 0.5*AliTRDgeometry::CamHght(); 
  xPlane5     = AliTRDgeometry::GetTime0(5) 
              - AliTRDgeometry::CdrHght()
              - 0.5*AliTRDgeometry::CamHght();
  fXprojPlane = 0.5 * (xPlane0 + xPlane5);

}

