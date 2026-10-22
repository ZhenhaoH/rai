/*  ------------------------------------------------------------------
    Copyright (c) 2011-2024 Marc Toussaint
    email: toussaint@tu-berlin.de

    This code is distributed under the MIT License.
    Please see <root-path>/LICENSE for details.
    --------------------------------------------------------------  */

#ifdef RAI_PYBIND

#include "types.h"
#include "../LGP/LGP_Tool.h"

namespace {
struct PyLGP_ActionTranslator : rai::LGP_ActionTranslator {
  std::shared_ptr<KOMO> setup_sequence(rai::Configuration& C, uint K) override {
    PYBIND11_OVERRIDE_PURE(std::shared_ptr<KOMO>, rai::LGP_ActionTranslator, setup_sequence, C, K);
  }
  std::shared_ptr<KOMO> setup_motion(rai::Configuration& C, uint K) override {
    PYBIND11_OVERRIDE_PURE(std::shared_ptr<KOMO>, rai::LGP_ActionTranslator, setup_motion, C, K);
  }
  void add_action_constraints(std::shared_ptr<KOMO>& komo, double time, const StringA& action) override {
    PYBIND11_OVERRIDE_PURE(void, rai::LGP_ActionTranslator, add_action_constraints, komo, time, action);
  }
  void add_action_constraints_motion(std::shared_ptr<KOMO>& komo, double time, const StringA& prev_action, const StringA& action, uint actionPhase) override {
    PYBIND11_OVERRIDE_PURE(void, rai::LGP_ActionTranslator, add_action_constraints_motion, komo, time, prev_action, action, actionPhase);
  }
};

pybind11::dict lgp_status(const rai::LGP_Tool& tool) {
  pybind11::dict result;
  result["status"]=tool.getStatus();
  result["steps"]=tool.step_count;
  result["symbolic_steps"]=tool.tamp.getSymbolicSteps();
  result["solution_count"]=tool.solutions.N;
  return result;
}
}

void init_LGP(pybind11::module& m) {
  m.attr("ROBOT_POLICY_LGP_API")=1;

  pybind11::class_<rai::LGP_ActionTranslator, PyLGP_ActionTranslator, shared_ptr<rai::LGP_ActionTranslator>>(m, "LGP_ActionTranslator")
      .def(pybind11::init<>())
      .def("setup_sequence", &rai::LGP_ActionTranslator::setup_sequence)
      .def("setup_motion", &rai::LGP_ActionTranslator::setup_motion)
      .def("add_action_constraints", &rai::LGP_ActionTranslator::add_action_constraints)
      .def("add_action_constraints_motion", &rai::LGP_ActionTranslator::add_action_constraints_motion);

  pybind11::class_<rai::LGP_TAMP_Abstraction, shared_ptr<rai::LGP_TAMP_Abstraction>>(m, "LGP_TAMP_Abstraction", "LGP_TAMP_Abstraction")
      .def("setup_sequence", &rai::LGP_TAMP_Abstraction::setup_sequence)
      .def("setup_motion", &rai::LGP_TAMP_Abstraction::setup_motion)
      .def("add_action_constraints", &rai::LGP_TAMP_Abstraction::add_action_constraints)
      .def("add_action_constraints_motion", &rai::LGP_TAMP_Abstraction::add_action_constraints_motion);

  pybind11::class_<rai::LGP_Tool, shared_ptr<rai::LGP_Tool>>(m, "LGP_Tool", "Tools to compute things (and solve) a Task-and-Motion Planning problem formulated as Logic-Geometric Program")
      .def(pybind11::init<rai::Configuration&, rai::LGP_TAMP_Abstraction&>(), "initialization",
           pybind11::keep_alive<1, 2>(), pybind11::keep_alive<1, 3>())
      .def("setLimits", &rai::LGP_Tool::setLimits,
           pybind11::arg("max_steps")=256, pybind11::arg("max_symbolic_steps")=10000,
           pybind11::arg("max_evaluations")=1000, pybind11::arg("max_motif_steps")=50)
      .def("step", [](rai::LGP_Tool& self) {
        { pybind11::gil_scoped_release release; self.step(); }
        return lgp_status(self);
      }, "Run one bounded scheduling step; a native optimizer is not preemptible")
      .def("status", &lgp_status)
      .def("cancel", &rai::LGP_Tool::cancel)
      .def("solve", &rai::LGP_Tool::solve, "compute new solution within limits, or raise RuntimeError",
           pybind11::arg("verbose")=1, pybind11::call_guard<pybind11::gil_scoped_release>())
      .def("getSolvedPlan", &rai::LGP_Tool::getSolvedPlan, "return list of discrete decisions of current solution")
      .def("getSolvedKOMO", &rai::LGP_Tool::getSolvedKOMO, "return the solved waypoint KOMO of current solution")
      .def("get_piecewiseMotionProblem", &rai::LGP_Tool::get_piecewiseMotionProblem, "return an unsolved phase KOMO", pybind11::arg("phase"), pybind11::arg("fixEnd"))
      .def("get_fullMotionProblem", &rai::LGP_Tool::get_fullMotionProblem, "return the unsolved full-motion KOMO; check NLP_Solver.feasible before execution", pybind11::arg("initWithWaypoints"))
      .def("solvePiecewiseMotions", &rai::LGP_Tool::solvePiecewiseMotions, "legacy convenience method; does not certify motion feasibility", pybind11::arg("verbose")=1)
      .def("solveFullMotion", &rai::LGP_Tool::solveFullMotion, "legacy convenience method; does not certify motion feasibility", pybind11::arg("verbose")=1)
      .def("view_solved", &rai::LGP_Tool::view_solved, "view last computed solution", pybind11::arg("pause"))
      .def("view_close", &rai::LGP_Tool::view_close, "");

  m.def("default_LGP_TAMP_Abstraction", &rai::default_LGP_TAMP_Abstraction,
        "Keep native FOL/AStar search; optionally delegate geometry to Python",
        pybind11::arg("C"), pybind11::arg("lgp_config_file"), pybind11::arg("translator")=nullptr,
        pybind11::keep_alive<0, 1>(), pybind11::keep_alive<0, 3>());
}

#endif
