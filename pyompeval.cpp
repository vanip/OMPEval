#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/functional.h>

#include "omp/Constants.h"
#include "omp/CardRange.h"
#include "omp/Hand.h"
#include "omp/HandEvaluator.h"
#include "omp/EquityCalculator.h"

namespace py = pybind11;
PYBIND11_MODULE(pyomp, m) {
    m.doc() = "Python Wrapper Library for OMP Poker Eval";

    m.attr("HAND_CATEGORY_OFFSET") = py::int_(omp::HAND_CATEGORY_OFFSET);
    m.attr("HAND_CATEGORY_SHIFT") = py::int_(omp::HAND_CATEGORY_SHIFT);
    m.attr("HIGH_CARD") = py::int_(omp::HIGH_CARD);
    m.attr("PAIR") = py::int_(omp::PAIR);
    m.attr("TWO_PAIR") = py::int_(omp::TWO_PAIR);
    m.attr("THREE_OF_A_KIND") = py::int_(omp::THREE_OF_A_KIND);
    m.attr("STRAIGHT") = py::int_(omp::STRAIGHT);
    m.attr("FLUSH") = py::int_(omp::FLUSH);
    m.attr("FULL_HOUSE") = py::int_(omp::FULL_HOUSE);
    m.attr("FOUR_OF_A_KIND") = py::int_(omp::FOUR_OF_A_KIND);
    m.attr("STRAIGHT_FLUSH") = py::int_(omp::STRAIGHT_FLUSH);

    py::class_<omp::CardRange>(m, "CardRange")
            .def(py::init<>())
            .def(py::init<const std::string &>())
            .def(py::init<const char *>())
            .def(py::init<const std::vector<std::array<uint8_t,2>> &>())
            .def("combinations", &omp::CardRange::combinations)
            .def_static("getCardMask", &omp::CardRange::getCardMask, "static method for cardmask like 8sAdTd");

    py::class_<omp::Hand>(m, "Hand")
            .def(py::init<>())
            .def(py::init<const omp::Hand&>())
            .def(py::init<unsigned>())
            .def(py::init<std::array<uint8_t,2>>())
            .def(py::self + py::self)
            .def(py::self += py::self)
            .def(py::self - py::self)
            .def(py::self -= py::self)
            .def(py::self == py::self)
            .def_static("empty", &omp::Hand::empty)
            .def("suitCount", &omp::Hand::suitCount)
            .def("count", &omp::Hand::count)
            .def("hasFlush", &omp::Hand::hasFlush)
            .def("rankKey", &omp::Hand::rankKey)
            .def("flushKey", &omp::Hand::flushKey);

    py::class_<omp::HandEvaluator>(m, "HandEvaluator")
            .def(py::init<>())
            .def("evaluate", &omp::HandEvaluator::evaluate<true>, "evaluate hand");

    py::class_<omp::EquityCalculator::Results>(m, "Results")
            .def(py::init<>())
            .def_readwrite("players", &omp::EquityCalculator::Results::players)
            .def_readwrite("equity", &omp::EquityCalculator::Results::equity)
            .def_readwrite("wins", &omp::EquityCalculator::Results::wins)
            .def_readwrite("ties", &omp::EquityCalculator::Results::ties)
            .def_readwrite("hands", &omp::EquityCalculator::Results::hands)
            .def_readwrite("intervalHands", &omp::EquityCalculator::Results::intervalHands)
            .def_readwrite("time", &omp::EquityCalculator::Results::time)
            .def_readwrite("intervalTime", &omp::EquityCalculator::Results::intervalTime)
            .def_readwrite("progress", &omp::EquityCalculator::Results::progress)
            .def_readwrite("speed", &omp::EquityCalculator::Results::speed)
            .def_readwrite("intervalSpeed", &omp::EquityCalculator::Results::intervalSpeed)
            .def_readwrite("stdev", &omp::EquityCalculator::Results::stdev)
            .def_readwrite("skippedPrelopCombos", &omp::EquityCalculator::Results::skippedPreflopCombos)
            .def_readwrite("evaluatedPreflopCombos", &omp::EquityCalculator::Results::evaluatedPreflopCombos)
            .def_readwrite("evaluations", &omp::EquityCalculator::Results::evaluations)
            .def_readwrite("enumerateAll", &omp::EquityCalculator::Results::enumerateAll)
            .def_readwrite("finished", &omp::EquityCalculator::Results::finished);

    py::class_<omp::EquityCalculator>(m, "EquityCalculator")
            .def(py::init<>())
            .def("getResults", &omp::EquityCalculator::getResults, "get Results Object")
            .def("stop", &omp::EquityCalculator::stop, "stop need call wait before this function")
            .def("wait", &omp::EquityCalculator::wait, py::call_guard<py::gil_scoped_release>(), "wait threads")
            .def("start", &omp::EquityCalculator::start, py::call_guard<py::gil_scoped_release>(), "start equity calculation, call wait() after this",
                    py::arg("cardranges"), py::arg("boardcards") = 0, py::arg("deadcards") = 0,
                    py::arg("enumerateall") = false, py::arg("stdevtarget") = 5e-5, py::arg("callback") = nullptr,
                    py::arg("updateinterval") = 0.2, py::arg("threadcount") = 0)
            .def("setTimeLimit", &omp::EquityCalculator::setTimeLimit)
            .def("setHandLimit", &omp::EquityCalculator::setHandLimit)
            .def("handRanges", &omp::EquityCalculator::handRanges);
}
