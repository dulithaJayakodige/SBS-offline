#ifndef ROOT_SBSCherenkov_ClusterList
#define ROOT_SBSCherenkov_ClusterList

//****************************************************************
// The header file for the "ClusterRICH.C"
//****************************************************************

#include "TObject.h"
#include "TList.h"

class THaTrack;
class TClonesArray;

#include <iostream>
#include <stdio.h>

// Data class contains the data of a single PMT
// (i,j) coordinate of a pad; (x,y) coordinated of a pad; ADC value
// and a Veto to point it cannot be a local minimum inside the cluster
// useful to tell overlapping clusters apart). 
// Above all it contains a module to compare adc values. This allows 
// the ordering according the adc values itself of the components of a cluster.

class SBSCherenkov_Hit : public TObject {

 public:
 SBSCherenkov_Hit() 
   : fFlag(0), fVeto(0) {}
 SBSCherenkov_Hit( Int_t pmtnum, Int_t TDC_r, Int_t TDC_f, Int_t ADC, Int_t i, Int_t j, 
		Float_t x, Float_t y ) :
  fPMTNum(pmtnum), fTDC_r(TDC_r), fTDC_f(TDC_f), fADC(ADC), 
    fRow(i), fCol(j), fX(x), fY(y), fFlag(0),
    fVeto(0), tdcr_set(false), tdcf_set(false) {}
  virtual ~SBSCherenkov_Hit() {}
  
  void       Show(FILE * fout1);
  void       Show(FILE * fout1, FILE * fout2);
  
  Int_t      GetPMTNum()   const {return fPMTNum;}
  Float_t    GetX()        const {return fX;}
  Float_t    GetY()        const {return fY;}
  Int_t      GetRow()      const {return fRow;}
  Int_t      GetCol()      const {return fCol;}
  Int_t      GetADC()      const {return fADC;}
  Int_t      GetTDC_r()    const {return fTDC_r;}
  Int_t      GetTDC_f()    const {return fTDC_f;}
  Int_t      GetFlag()     const {return fFlag;}
  Int_t      GetVeto()     const {return fVeto;} 
  void       SetPMTNum( Int_t pmtnum ) {fPMTNum = pmtnum;}
  void       SetX( Float_t x )         {fX = x;}
  void       SetY( Float_t y )         {fY = y;}
  void       SetRow( Int_t i )         {fRow = i;}
  void       SetCol( Int_t j )         {fCol = j;}
  void       SetADC( Int_t ADC )       {fADC = ADC;}
  void       SetTDC_r( Int_t TDC_r )   {fTDC_r = TDC_r;}
  void       SetTDC_f( Int_t TDC_f )   {fTDC_f = TDC_f;}
  void       SetFlag( Int_t Flag )     {fFlag = Flag;}
  void       SetVeto( Int_t Veto )     {fVeto = Veto;}

  virtual Int_t   Compare( const TObject* ) const;
  virtual Bool_t  IsSortable() const { return kTRUE; }
  
  Bool_t     TDC_risSet() {return tdcr_set;}
  Bool_t     TDC_fisSet() {return tdcf_set;}

private:
  Int_t     fPMTNum; // Hit PMT number
  Int_t     fTDC_r;  // Hit rise time TDC
  Int_t     fTDC_f;  // Hit fall time TDC
  Int_t     fADC;    // Hit ADC /!\ deduced from TDC values
  Int_t     fRow;      // Hit row number in PMT matrix
  Int_t     fCol;      // Hit column number in PMT matrix
  Float_t   fX;      // Hit X position in PMT matrix
  Float_t   fY;      // Hit Y position in PMT matrix
  Int_t     fFlag;   // ?
  Int_t     fVeto;   // ?
  
  Bool_t tdcr_set;// lead TDC is set
  Bool_t tdcf_set;// fall TDC is set
  
  ClassDef(SBSCherenkov_Hit,0)   //A hit in the RICH
};


// --------------------------------------------------------------

// Cluster: List of Hits of elements that make up a cluster in GRINCH. 
// Specifically, in the GRINCH, a cluster is a list of adjacent PMT hits;
// 

class SBSCherenkov_Cluster : public TObject {
 public:
  SBSCherenkov_Cluster();
  SBSCherenkov_Cluster( const SBSCherenkov_Cluster& rhs );
  SBSCherenkov_Cluster& operator=( const SBSCherenkov_Cluster& rhs );

  ~SBSCherenkov_Cluster() { delete fHitList; }
  
  void    Clear( Option_t* opt="" );
  void    Insert( SBSCherenkov_Hit* theHit );
  void    Remove( SBSCherenkov_Hit* theHit );
  
  Bool_t  IsNeighbor( const SBSCherenkov_Hit* theHit,  Float_t par);
  
  Int_t   GetNHits()   const { return fHitList->GetSize(); }
  TList*  GetHitList()      { return fHitList; }
  
  Float_t GetXcenter() const { return fXcenter; }
  Float_t GetYcenter() const  { return fYcenter; }
  Float_t GetXcenter_w() const { return fXcenter_w; }
  Float_t GetYcenter_w() const  { return fYcenter_w; }
  Float_t GetCharge()  const     { return fCharge; }
  
  Float_t GetMeanRisingTime() const { return fMeanRisingTime; }
  Float_t GetMeanFallingTime() const { return fMeanFallingTime; }
  Float_t GetRisingTimeRMS() const    { return fRisingTimeRMS; }
  Float_t GetFallingTimeRMS() const    { return fFallingTimeRMS; }

  THaTrack* GetTrack() const            { return fTrack; }

  void    SetXcenter(Float_t xcenter)    { fXcenter = xcenter; }
  void    SetYcenter(Float_t ycenter)     { fYcenter = ycenter; }
  void    SetXcenter_w(Float_t xcenter_w)  { fXcenter_w = xcenter_w; }
  void    SetYcenter_w(Float_t ycenter_w)   { fYcenter_w = ycenter_w; }
  void    SetCharge(Float_t charge)          { fCharge = charge; }
  
  void    SetMeanRisingTime(Float_t meanrisingtime)  { fMeanRisingTime = meanrisingtime; }
  void    SetMeanFallingTime(Float_t meanfallingtime) { fMeanFallingTime = meanfallingtime; }
  void    SetRisingTimeRMS(Float_t risingtimerms)      { fRisingTimeRMS = risingtimerms; }
  void    SetFallingTimeRMS(Float_t fallingtimerms)     { fFallingTimeRMS = fallingtimerms; }
  
  void    SetTrack( THaTrack* track ) { fTrack = track; }

  void    MergeCluster( const SBSCherenkov_Cluster& rhs );
  
 private:
  TList*     fHitList;   //List of hits belonging to this cluster
  
  Float_t    fXcenter;   // X mean of all hits in the list
  Float_t    fYcenter;   // Y mean of all hits in the list
  Float_t    fXcenter_w; // Weighted X mean : (Sum of x*adc)/(sum adc) of all hits in the list
  Float_t    fYcenter_w; // Weighted Y mean : (Sum of y*adc)/(sum adc) of all hits in the list
  Float_t    fCharge;    // Sum of ADCs
  
  Float_t    fMeanRisingTime;  // Mean rising time of all hits in the list
  Float_t    fMeanFallingTime; // Mean falling time of all hits in the list
  Float_t    fRisingTimeRMS;   // Rising time RMS of all hits in the list
  Float_t    fFallingTimeRMS;  // Falling time RMS of all hits in the list
  
  Bool_t     fTrackMatch;// true if a track can be matched to the cluster
  THaTrack*  fTrack;     // Track best associated with this cluster
  
  ClassDef(SBSCherenkov_Cluster,0)  //A cluster of hits in the GRINCH
};

#endif


















