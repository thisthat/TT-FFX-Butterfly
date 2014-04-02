typedef std::pair<int, char> Key;
typedef std::pair<int,std::vector<int> > Out;
typedef std::map<Key,Out> Map;

enum STATE {NOPE, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

class Automata {

	public:
        Automata();
        ~Automata();
 		void transition(STATE const s);
    private:
    	Map tr;
};
/*
Key k1 = std::make_pair(0, 'a');
  int myints[] = {16,2};
  std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
  Out o1 = std::make_pair(1, v);
  
  m[k1] = o1;
  Out o = m.begin()->second;
  Key k = m.begin()->first;
  printf("mapa[%d,%c] --> %d\n", k.first, k.second, o.first);
  for (int index=0; index<2; ++index) {
        std::cout << "\t" << o.second[index] << std::endl;
    }
*/