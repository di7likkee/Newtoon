#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int HEIGHT_MAP = 20;//размер карты высота
const int WIDTH_MAP = 150;//размер карты ширина 


String TileMapOrigin[HEIGHT_MAP] = {
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"0                                                        p   p                                         pp           p                                0",
	"0                                                      1 p   p                       a                 pp           p4                               0",
	"0                                                        p a p        a                             a  pp aaa       p       aa                       0",
	"0                                                        p   p               a          a              pp           p      a  a    a    a            0",
	"0                                                    ppppp a p       pp      b          b          pp  ppppppp      ppppp  a      aaa  aaa           0",
	"0                                a                           p      dpp                           bpp        p      p      a  a    a    a            0",
	"0                                                            p       pp  b           b             pp a      p   d  p       aa                       0",
	"0                                pp             pp   a  a  a p       pp                      a     pp        p      p                                0",
	"0                       aa     ppp              pp           pd      pp                      b     pp               p                                0",
	"0               a              pp         pp    pppppppppppppp       pp                            ppppppp      d   p                                0",
	"0                      ppppp   pp               pp          pp       pp          a        b        pp a pp          p  a  a aaa a   a                0",
	"0             ppppp            pp               pp       a  pp  a    pp          b                 pp a pp          p  a  a a    a a     a    a      0",
	"0                              pp   p      a    p     a     pp  d    pp              b             pp   pp     d    p  aaaa aa    a     a a  a a     0",
	"0                                                        a  pp       pp                            pp a             p  a  a a     a        aa        0",
	"0         p                                p         pp     pp2      pp                          1 pp           3   p  a  a aaa   a                  0",
	"0        pp     a      a       a         ppp        ppp  a  pp      dpp                            pp a  a   d      p                                0",
	"0       ppp                             pppp       pppp     pp       pp                            pp               p                                0",
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",

};