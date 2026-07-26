#include "formatters/templateLoader.hpp"
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "support/temp_directory.hpp"

TEST(TemplateLoaderTest, LoadsFilesFromProvidedDirectory) {
  TempDirectory temp;

  temp.createFile(".clang-format", "contents");
  temp.createFile(".rustfmt", "contents");

  option::TemplateLoader loader(temp.path().string());

  const auto formatters = loader.GetFormatters();

  EXPECT_EQ(formatters.size(), 2);
  EXPECT_NE(loader.getFormatter(".clang-format"), nullptr);
  EXPECT_NE(loader.getFormatter(".rustfmt"), nullptr);
}
