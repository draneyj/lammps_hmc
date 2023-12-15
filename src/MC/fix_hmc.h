/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(hmc, FixHMC)

#else

#ifndef LMP_FIX_HMC_H
#define LMP_FIX_HMC_H

#include "atom.h"
#include "fix.h"
#include "fix_rigid_small.h"

namespace LAMMPS_NS {

class FixHMC : public Fix {
 public:
  FixHMC(class LAMMPS *, int, char **);
  ~FixHMC();
  void post_constructor();
  int setmask();
  void init();
  void setup(int);
  void end_of_step();
  double compute_scalar();
  double compute_vector(int);

  int pack_forward_comm(int, int *, double *, int, int *);
  void unpack_forward_comm(int, int, double *);
  int pack_reverse_comm(int, int, double *);
  void unpack_reverse_comm(int, int *, double *);
  void grow_arrays(int);
  void copy_arrays(int, int, int);
  int pack_exchange(int, double *);
  int unpack_exchange(int, double *);
  double memory_usage();

 private:
  void setup_arrays_and_pointers();
  void add_new_computes();
  void tune_parameter(int *, const char *);
  void save_current_state();
  void restore_saved_state();
  void random_velocities();
  void rigid_body_random_velocities();
  template <typename T> void store_peratom_member(Atom::PerAtom &, Atom::PerAtom, int, int, int);
  template <typename T> void restore_peratom_member(Atom::PerAtom, Atom::PerAtom &, int);
  template <typename T> double memory_usage_peratom_member(Atom::PerAtom &);
  std::vector<Atom::PerAtom> stored_peratom;
  std::vector<Atom::PerAtom> current_peratom;
  tagint *stored_tag;
  int stored_nlocal, stored_nghost, stored_ntotal, stored_nmax;
  int stored_nbonds, stored_nangles, stored_ndihedrals, stored_nimpropers;
  FixRigidSmall::Body *stored_body;
  int stored_nlocal_body, stored_nghost_body, stored_ntotal_body;
  int *stored_bodyown;
  tagint *stored_bodytag;
  int *stored_atom2body;
  imageint *stored_xcmimage;
  double **stored_displace;
  int *stored_eflags;
  double **stored_orient;
  double **stored_dorient;

  int resample_on_accept_flag, mom_flag;

  char *mdi;
  class FixNVE *fix_nve;
  class FixRigidSmall *fix_rigid;

  int nattempts, naccepts;
  double KT, mbeta;
  double PE, KE;
  double DeltaPE, DeltaKE;

  class RanPark *random;
  class RanPark *random_equal;

  int ne;
  int *rev_comm;
  double **eatom;
  double ***eatomptr;

  int neg;
  double *eglobal;
  double **eglobalptr;

  int nv;
  double **vglobal;
  double ***vglobalptr;
  double ***vatom;
  double ****vatomptr;

  class Compute *pe;
  class Compute *ke;
  class Compute *peatom;
  class Compute *press;
  class Compute *pressatom;

  int peatom_flag;
  int press_flag;
  int pressatom_flag;

  int comm_flag;
  int nvalues;
  int ncommrev;

  double (*itensor)[6];

  static const size_t three = 3 * sizeof(double);
  static const size_t four = 4 * sizeof(double);
  static const size_t six = 6 * sizeof(double);
};

}    // namespace LAMMPS_NS

#endif
#endif

    /* ERROR/WARNING messages:

*/