// Copyright 2024 Dostavalov Semyon

#include "core/task/include/task.hpp"
#include <vector>
#include <string>

namespace dostavalov_s_seq {
    const double TOLERANCE = 0.0001;
    const double MIN_VALUE = 0.0;
    const double MAX_VALUE = 50.0;

    std::vector<double> randVector(int size);
    std::vector<double> randMatrix(int size);

    class SeqSLAYGradient: public ppc::core::Task {
        public:
            explicit SeqSLAYGradient(std::shared_ptr
                                     <ppc::core::TaskData> taskData_)
                                      : Task(std::move(taskData_)) {}

            bool pre_processing() override;
            bool validation() override;
            bool run() override;
            bool post_processing() override;
            bool check_solution(const std::vector<double>& a,
                                const std::vector<double>& b,
                                const std::vector<double>& x);

        private:
            std::vector<double> matrix, vector, answer;
    };

}  // namespace dostavalov_s_seq
