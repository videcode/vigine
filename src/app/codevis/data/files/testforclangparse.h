class SomeClass {
public:
  SomeClass() {
    this->x = 1;
    if (x > 0) {
      this->x = 2;
    }
  }
  int x{0};
};
