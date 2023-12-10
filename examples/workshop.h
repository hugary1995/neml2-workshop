#pragma once

#include <iostream>

#include "neml2/tensors/tensors.h"
#include "neml2/base/HITParser.h"
#include "neml2/base/Factory.h"

/**
 * @brief Print workshop preface
 *
 */
void workshop_preface();

/**
 * @brief Print a pretty title line
 *
 * @param title The centered title to print
 * @param pad Spacing around the title text
 * @param n Total width of the title line
 */
void print_title(const std::string_view title = "", const size_t pad = 3, const size_t n = 79);

/**
 * @brief Print a general object by stringifying it
 *
 * @param x Something to print
 * @param title The centered title to print
 * @param pad Spacing around the title text
 * @param n Total width of the title line
 */
template <typename T>
void print_general(const T & x, const std::string_view title = "", const size_t pad = 3, const size_t n = 79);

/**
 * @brief Format print a torch::Tensor
 *
 * @param x The torch tensor to print
 * @param title The centered title to print
 * @param pad Spacing around the title text
 * @param n Total width of the title line
 */
void print_torch_tensor(const torch::Tensor & x,
                        const std::string_view title = "",
                        const size_t pad = 3,
                        const size_t n = 79);

/**
 * @brief Format print meta information about a torch::Tensor
 *
 * @param x The torch tensor to print
 * @param title The centered title to print
 * @param pad Spacing around the title text
 * @param n Total width of the title line
 */
void print_torch_tensor_info(const torch::Tensor & x,
                             const std::string_view title = "",
                             const size_t pad = 3,
                             const size_t n = 79);
/**
 * @brief Format print meta information about a neml2::BatchTensor
 *
 * @param x The NEML2 tensor to print
 * @param title The centered title to print
 * @param pad Spacing around the title text
 * @param n Total width of the title line
 */
void print_neml2_tensor_info(const neml2::BatchTensor & x,
                             const std::string_view title = "",
                             const size_t pad = 3,
                             const size_t n = 79);

/**
 * @brief Parse and manufacture a NEML2 input file, then get the specified NEML2 object named \p
 * name under section \p section.
 *
 * @param path Path to the input file
 * @param section Section under which to look for the object
 * @param name Name of the object
 */
template <class T>
T & load(const std::string & path, const std::string & section, const std::string & name);

std::string
root_dir()
{
  return std::string(ROOT_DIR) + "/";
}

///////////////////////////////////////////////////////////////////////////////
// Implementations
///////////////////////////////////////////////////////////////////////////////

template <typename T>
void
print_general(const T & x, const std::string_view title, const size_t pad, const size_t n)
{
  print_title(title, pad, n);

  std::cout << neml2::utils::stringify(x) << std::endl << std::endl;
}

template <class T>
T &
load(const std::string & path, const std::string & section, const std::string & name)
{
  neml2::Factory::clear();
  neml2::HITParser parser;
  const auto all_options = parser.parse(path, "");
  neml2::Factory::load(all_options);
  return neml2::Factory::get_object<T>(section, name);
}
