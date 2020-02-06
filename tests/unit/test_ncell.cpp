#include <iostream>
#include <ncell.h>

int main () {

  sico::utl::ncell< 2 > cell2d {};
  sico::utl::ncell< 3 > cell3d {};
  sico::utl::ncell< 4 > cell4d {};

  std::cout << cell2d.sub_cell.size() << "\t" << cell3d.sub_cell.size() << "\t" << cell4d.sub_cell.size() << std::endl;

  return 0;

}
