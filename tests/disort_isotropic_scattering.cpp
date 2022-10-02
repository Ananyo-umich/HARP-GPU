extern "C" {
  #include <cdisort.h>
}

/*
 * Disort-specific shift macros.
 * Using unit-offset shift macros to match Fortran version
 */

#undef  DTAUC
#define DTAUC(lc)  ds.dtauc[lc-1]
#undef  PHI
#define PHI(j)     ds.phi[j-1]
#undef  PMOM
#define PMOM(k,lc) ds.pmom[k+(lc-1)*(ds.nmom_nstr+1)]
#undef  SSALB
#define SSALB(lc)  ds.ssalb[lc-1]
#undef  TEMPER
#define TEMPER(lc) ds.temper[lc]
#undef  UMU
#define UMU(iu)    ds.umu[iu-1]
#undef  UTAU
#define UTAU(lu)   ds.utau[lu-1]

/*
 * Disotest-specific shift macros
 */
#undef  GOODUU
#define GOODUU(iu,lu,j) good.uu[iu-1+(lu-1+(j-1)*ds.ntau)*ds.numu]


int main(int argc, char **argv) {
  const int
    ncase = 6;
  char
    abc[] = "abcdefghijklmnopqrstuvwxyz";
  disort_state
    ds;
  disort_output
    out,good;
  register int
    icas;
  //extern void
    //  c_disort(),c_errmsg(),c_getmom();

  ds.accur = 0.;
  ds.flag.prnt[0]=true;
  ds.flag.prnt[1]=false;
  ds.flag.prnt[2]=false;
  ds.flag.prnt[3]=false;
  ds.flag.prnt[4]=false;

  ds.flag.ibcnd  = GENERAL_BC;
  ds.flag.usrtau = true;
  ds.flag.usrang = true;
  ds.flag.lamber = true;
  ds.flag.planck = false;
  ds.flag.onlyfl = false;
  ds.flag.quiet  = true;
  ds.flag.spher  = false;
  ds.flag.general_source           = false;
  ds.flag.output_uum = false;
  ds.flag.intensity_correction = true;
  ds.flag.old_intensity_correction = true;

  ds.nlyr   = 1;
  ds.nstr   = 16;
  ds.nphase = ds.nstr;
  ds.nmom   = ds.nstr;
  ds.nphi   = 1;
  ds.numu   = 6;
  ds.ntau   = 2;

  ds.flag.brdf_type = BRDF_NONE;

  /* Allocate memory */
  c_disort_state_alloc(&ds);
  c_disort_out_alloc(&ds,&good);
  
  c_getmom(ISOTROPIC,0.,ds.nmom,ds.pmom);

  UTAU(1)   =  0.;
  UMU(1)    = -1.;
  UMU(2)    = -0.5;
  UMU(3)    = -0.1;
  UMU(4)    =   .1;
  UMU(5)    =   .5;
  UMU(6)    =  1.;
  PHI(1)    =  0.;

  ds.bc.umu0   =   .1;
  ds.bc.phi0   =  0.;
  ds.bc.albedo =  0.;
  ds.bc.fluor  =  0.;

  for (icas = 1; icas <= ncase; icas++) {
    switch(icas) {
      case 1:
        UTAU(2)  = .03125;
        SSALB(1) = .2;

        ds.bc.fbeam = M_PI/ds.bc.umu0;
        ds.bc.fisot = 0.0;

        /* Correct answers */ 
        good.rad[0].rfldir=3.14159,    good.rad[1].rfldir=2.29844;
        good.rad[0].rfldn =0.,         good.rad[1].rfldn =7.94108E-02;
        good.rad[0].flup  =7.99451E-02,good.rad[1].flup  =0.;
        good.rad[0].dfdt  =2.54067E+01,good.rad[1].dfdt  =1.86531E+01;
        GOODUU(1,1,1) =0.,        GOODUU(2,1,1)=0.,         GOODUU(3,1,1)=0.,         GOODUU(4,1,1)=1.17771E-01,GOODUU(5,1,1)=2.64170E-02,GOODUU(6,1,1)=1.34041E-02,
        GOODUU(1,2,1)=1.33826E-02,GOODUU(2,2,1)=2.63324E-02,GOODUU(3,2,1)=1.15898E-01,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
      case 2:
        UTAU(2)  =  .03125;
        SSALB(1) = 1.;

        ds.bc.fbeam = M_PI/ds.bc.umu0;
        ds.bc.fisot = 0.0;

        /* Correct answers */
        good.rad[0].rfldir=3.14159,    good.rad[1].rfldir=2.29844;
        good.rad[0].rfldn =0.,         good.rad[1].rfldn =4.20233E-01;
        good.rad[0].flup  =4.22922E-01,good.rad[1].flup  =0.;
        good.rad[0].dfdt  =0.,         good.rad[1].dfdt  =0.;
        GOODUU(1,1,1)=0.,         GOODUU(2,1,1)=0.,         GOODUU(3,1,1)=0.,         GOODUU(4,1,1)=6.22884E-01,GOODUU(5,1,1)=1.39763E-01,GOODUU(6,1,1)=7.09192E-02,
        GOODUU(1,2,1)=7.08109E-02,GOODUU(2,2,1)=1.39337E-01,GOODUU(3,2,1)=6.13458E-01,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
      case 3:
        UTAU(2)  = .03125;
        SSALB(1) = .99;

        ds.bc.fbeam = 0.;
        ds.bc.fisot = 1.;

        /* Correct answers */
        good.rad[0].rfldir=0.,         good.rad[1].rfldir=0.;
        good.rad[0].rfldn =3.14159,    good.rad[1].rfldn =3.04897;
        good.rad[0].flup  =9.06556E-02,good.rad[1].flup  =0.;
        good.rad[0].dfdt  =6.66870E-02,good.rad[1].dfdt  =5.88936E-02;
        GOODUU(1,1,1)=1.,         GOODUU(2,1,1)=1.,         GOODUU(3,1,1)=1.,         GOODUU(4,1,1)=1.33177E-01,GOODUU(5,1,1)=2.99879E-02,GOODUU(6,1,1)=1.52233E-02,
        GOODUU(1,2,1)=9.84447E-01,GOODUU(2,2,1)=9.69363E-01,GOODUU(3,2,1)=8.63946E-01,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
      case 4:
        UTAU(2)  = 32.;
        SSALB(1) =   .2;

        ds.bc.fbeam = M_PI/ds.bc.umu0;
        ds.bc.fisot = 0.0;

        /* Correct answers */
        good.rad[0].rfldir=3.14159,    good.rad[1].rfldir=0.;
        good.rad[0].rfldn =0.,         good.rad[1].rfldn =0.;
        good.rad[0].flup  =2.59686E-01,good.rad[1].flup  =0.;
        good.rad[0].dfdt  =2.57766E+01,good.rad[1].dfdt  =0.;
        GOODUU(1,1,1)=0.,         GOODUU(2,1,1)=0.,         GOODUU(3,1,1)=0.,         GOODUU(4,1,1)=2.62972E-01,GOODUU(5,1,1)=9.06967E-02,GOODUU(6,1,1)=5.02853E-02,
        GOODUU(1,2,1)=1.22980E-15,GOODUU(2,2,1)=1.30698E-17,GOODUU(3,2,1)=6.88840E-18,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
      case 5:
        UTAU(2)  = 32.;
        SSALB(1) =  1.;

        ds.bc.fbeam = M_PI/ds.bc.umu0;
        ds.bc.fisot = 0.0;

        /* Correct answers */
        good.rad[0].rfldir=3.14159,good.rad[1].rfldir=0.;
        good.rad[0].rfldn =0.,     good.rad[1].rfldn =6.76954E-02;
        good.rad[0].flup  =3.07390,good.rad[1].flup  =0.;
        good.rad[0].dfdt  =0.,     good.rad[1].dfdt  =0.;
        GOODUU(1,1,1)=0.,         GOODUU(2,1,1)=0.,         GOODUU(3,1,1)=0.,         GOODUU(4,1,1)=1.93321E+00,GOODUU(5,1,1)=1.02732E+00,GOODUU(6,1,1)=7.97199E-01,
        GOODUU(1,2,1)=2.71316E-02,GOODUU(2,2,1)=1.87805E-02,GOODUU(3,2,1)=1.16385E-02,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
      case 6:
        UTAU(2)  = 32.;
        SSALB(1) =   .99;

        ds.bc.fbeam = 0.;
        ds.bc.fisot = 1.;

        /* Correct answers */ 
        good.rad[0].rfldir=0.,         good.rad[1].rfldir=0.;
        good.rad[0].rfldn =3.14159,    good.rad[1].rfldn =4.60048E-03;
        good.rad[0].flup  =2.49618,    good.rad[1].flup  =0.;
        good.rad[0].dfdt  =1.14239E-01,good.rad[1].dfdt  =7.93633E-05;
        GOODUU(1,1,1)=1.,         GOODUU(2,1,1)=1.,         GOODUU(3,1,1)=1.,         GOODUU(4,1,1)=8.77510E-01,GOODUU(5,1,1)=8.15136E-01,GOODUU(6,1,1)=7.52715E-01,
        GOODUU(1,2,1)=1.86840E-03,GOODUU(2,2,1)=1.26492E-03,GOODUU(3,2,1)=7.79280E-04,GOODUU(4,2,1)=0.,         GOODUU(5,2,1)=0.,         GOODUU(6,2,1)=0.;
      break;
    }

    DTAUC(1) = UTAU(2);

    sprintf(ds.header,"Test Case No. 1%.1s:  Isotropic Scattering, Ref. VH1, Table 12:  b =%9.5f, a =%5.2f",abc+icas-1,UTAU(2),SSALB(1));

    c_disort_out_alloc(&ds,&out);
    c_disort(&ds,&out);

    print_test(&ds,&out,&ds,&good);
    c_disort_out_free(&ds,&out);
  }

  /* Free allocated memory. */
  c_disort_out_free(&ds,&good);
  c_disort_state_free(&ds);
}
