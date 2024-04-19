// Copyright 2024 Dostavalov Semyon
#include <gtest/gtest.h>

#include <vector>
#include "seq/dostavalov_s_sop_gradient/include/ops_seq.hpp"

namespace dostavalov_s_seq {
    std::shared_ptr<ppc::core::TaskData> 
createTaskData(std::vector<double> &matrix,std::vector<double> &vector,
               std::vector<double> &result) {
  std::shared_ptr<ppc::core::TaskData> taskDataSeq =
      std::make_shared<ppc::core::TaskData>();

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(
      matrix.data()));
  taskDataSeq->inputs_count.emplace_back(matrix.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>
      (vector.data()));
  taskDataSeq->inputs_count.emplace_back(vector.size());

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>
      (result.data()));
  taskDataSeq->outputs_count.emplace_back(result.size());

  return taskDataSeq;
}
TEST(dostavalov_s_sop_gradient, Test_Empty) {
      std::vector<double> matrix = {};
      std::vector<double> vector = {};

      std::vector<double> result(vector.size(), 0.0);
      std::vector<double> true_result = {};

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      for (int i = 0; i < result.size(); i++) {
        ASSERT_LE(std::abs(true_result[i] - result[i]), TOLERANCE);
      }
    }

    TEST(dostavalov_s_sop_gradient, Test_Drob_Size_4) {
      std::vector<double> matrix = {1.2, 3.4, 5.6, 7.8, 3.4, 9.1,
                                    2.3, 4.5, 5.6, 2.3, 8.9, 1.2,
                                    7.8, 4.5, 1.2, 6.7};

      std::vector<double> vector = {1.1, 2.2, 3.3, 4.4};

      std::vector<double> result(vector.size(), 0.0);
      std::vector<double> true_result = {0.521693, 0.025623,
                                         0.032353, 0.0263679};

      std::shared_ptr<ppc::core::TaskData> taskDataSeq = 
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      for (int i = 0; i < result.size(); i++) {
        ASSERT_LE(std::abs(true_result[i] - result[i]), TOLERANCE);
      }
    }

    TEST(dostavalov_s_sop_gradient, Test_Drob_Size_2) {
      std::vector<double> matrix = {2.1, 3.2, 3.2, 5.4};

      std::vector<double> vector = {1.2, 3.4};

      std::vector<double> result(vector.size(), 0.0);
      std::vector<double> true_result = {-4.0, 3.0};

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      for (int i = 0; i < result.size(); i++) {
        ASSERT_LE(std::abs(true_result[i] - result[i]), TOLERANCE);
      }
    }
    TEST(dostavalov_s_sop_gradient, Test_Size_4) {
      std::vector<double> matrix = {4.0, 2.0, 1.0, 3.0, 2.0, 5.0, 3.0, 
                                    1.0, 1.0, 3.0, 6.0, 2.0, 3.0, 1.0, 
                                    2.0, 7.0};

      std::vector<double> vector = {1.0, 2.0, 3.0, 4.0};

      std::vector<double> result(vector.size(), 0.0);
      std::vector<double> true_result = {-0.472727, 0.345455,
                                         0.181818, 0.672727};

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      for (int i = 0; i < result.size(); i++) {
        ASSERT_LE(std::abs(true_result[i] - result[i]), TOLERANCE);
      }
    }

    TEST(dostavalov_s_sop_gradient, Test_Size_2) {
      std::vector<double> matrix = {4.0, 1.0, 1.0, 3.0};

      std::vector<double> vector = {1.0, 2.0};

      std::vector<double> result(vector.size(), 0.0);
      std::vector<double> true_result = {0.0909091, 0.636364};

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      for (int i = 0; i < result.size(); i++) {
        ASSERT_LE(std::abs(true_result[i] - result[i]), TOLERANCE);
      }
    }

    TEST(dostavalov_s_sop_gradient, Test_Rand_300) {
      int size = 300;
      std::vector<double> matrix = randMatrix(size);
      std::vector<double> vector = randVector(size);

      std::vector<double> result(vector.size(), 0.0);

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      ASSERT_TRUE(testTaskSequential.check_solution(matrix, vector, result));
    }

    TEST(dostavalov_s_sop_gradient, Test_Rand_150) {
      int size = 150;
      std::vector<double> matrix = randMatrix(size);
      std::vector<double> vector = randVector(size);

      std::vector<double> result(vector.size(), 0.0);

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      ASSERT_TRUE(testTaskSequential.check_solution(matrix, vector, result));
    }
    TEST(dostavalov_s_sop_gradient, Test_Rand_1) {
      int size = 1;
      std::vector<double> matrix = randMatrix(size);
      std::vector<double> vector = randVector(size);

      std::vector<double> result(vector.size(), 0.0);

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      ASSERT_TRUE(testTaskSequential.check_solution(matrix, vector, result));
    }
    TEST(dostavalov_s_sop_gradient, Test_Rand_0) {
      int size = 0;
      std::vector<double> matrix = randMatrix(size);
      std::vector<double> vector = randVector(size);

      std::vector<double> result(vector.size(), 0.0);

      std::shared_ptr<ppc::core::TaskData> taskDataSeq =
          createTaskData(matrix, vector, result);

      SeqSLAYGradient testTaskSequential(taskDataSeq);

      ASSERT_EQ(testTaskSequential.validation(), true);
      testTaskSequential.pre_processing();
      testTaskSequential.run();
      testTaskSequential.post_processing();

      ASSERT_TRUE(testTaskSequential.check_solution(matrix, vector, result));
    }
    }
