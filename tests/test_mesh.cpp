// C/C++ header
#include <memory>

// Athena++
#include <mesh/mesh.hpp>

int main(int argc, char **argv) {
  IOWrapper infile;
  infile.Open("grid.inp", IOWrapper::FileMode::read);

  auto pin = std::make_unique<ParameterInput>();
  pin->LoadFromFile(infile);
  infile.Close();

  auto pmesh = std::make_unique<Mesh>(pin.get());
}
