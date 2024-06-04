#include <iostream>
#include <ostream>

using namespace std;

class Gate {
 public:
  Gate *input[2];
  virtual bool output() = 0;
  void setValue(Gate *, int);
  void setValue(bool, int);
};

class TRUE : public Gate {
 public:
  virtual bool output() { return 1; }
  void setValue(Gate *, int) {}
  void setValue(bool, int) {}
};

class FALSE : public Gate {
 public:
  virtual bool output() { return 0; }
  void setValue(Gate *, int) {}
  void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin) {
  if (val)
    this->input[pin] = &t;
  else
    this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate {
 public:
  virtual bool output() { return !(this->input[0]->output()); }
  void setValue(bool val, int pin = 0) {
    if (val)
      this->input[0] = &t;
    else
      this->input[0] = &f;
  }
  void setValue(Gate *gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate {
 public:
  virtual bool output() {
    return !(this->input[0]->output()) || !(this->input[1]->output());
  }
};

class NOR : public Gate {
 public:
  virtual bool output() {
    return !(this->input[0]->output()) && !(this->input[1]->output());
  }
};

class AND : public Gate {
 public:
  AND() : Gate() {}
  virtual bool output() {}

 private:
  Gate *component[2];
};

class OR : public Gate {
 public:
  OR() : Gate() {}
  virtual bool output() {}

 private:
  Gate *component[2];
};

class XOR : public Gate {
 public:
  XOR() : Gate() {}
  virtual bool output() {}

 private:
  Gate *component[5];
};

class Adder {
 public:
  virtual void setValue(bool, int) = 0;
  virtual void setValue(Gate *, int) = 0;
  virtual Gate *sum() = 0;
  virtual Gate *carryOut() = 0;
};

class OneBitHalfAdder : public Adder {
 public:
  OneBitHalfAdder() {}
  virtual void setValue(bool val, int pin) {}
  virtual void setValue(Gate *gate, int pin) {}
  virtual Gate *sum() {}
  virtual Gate *carryOut() {}

 private:
  Gate *component[2];
};

class OneBitFullAdder : public Adder {
 public:
  OneBitFullAdder() {}
  virtual void setValue(bool val, int pin) {}
  virtual void setValue(Gate *gate, int pin) {}
  virtual Gate *sum() {}
  virtual Gate *carryOut() {}

 private:
  Adder *a[2];
  Gate *carry;
};

class Decoder {
 public:
  virtual void setValue(bool, int) = 0;
  virtual void setValue(Gate *, int) = 0;
  virtual void setEnable(bool) = 0;
  virtual void setEnable(Gate *) = 0;
  virtual int output() = 0;
  virtual Gate *operator[](int) = 0;

 protected:
  Gate *enable;
};

class Decoder2_4 : public Decoder {
 public:
  Decoder2_4() : Decoder2_4(0) {}
  Decoder2_4(bool val) {
    if (val)
      this->enable = &t;
    else
      this->enable = &f;
    for (int i = 0; i < 2; i++) component[i] = new NOT;
    for (int i = 2; i < 6; i++) component[i] = new AND;
    for (int i = 0; i < 4; i++) enables[i] = new AND;
  }
  virtual void setEnable(bool val) {
    if (val)
      this->enable = &t;
    else
      this->enable = &f;
  }
  virtual void setEnable(Gate *gate) { this->enable = gate; }
  virtual void setValue(Gate *gate, int i) {
    component[i % 2]->input[0] = gate;
  }
  virtual void setValue(bool val, int i) {
    if (val)
      component[i % 2]->input[0] = &t;
    else
      component[i % 2]->input[0] = &f;
  }
  virtual Gate *operator[](int n) {
    _out();
    switch (n) {
      case 0:
        return enables[0];
      case 1:
        return enables[1];
      case 2:
        return enables[2];
      case 3:
        return enables[3];
      default:
        return nullptr;
    }
  }
  friend ostream &operator<<(ostream &out, Decoder2_4 dec) {
    for (int i = 3; i >= 0; i--) out << dec[i]->output() << " ";
    return out;
  }
  virtual int output() {
    for (int i = 0; i < 4; i++)
      if (enables[i]->output()) return i;
  }

 private:
  Gate *component[6];
  Gate *enables[4];

  void _out() {
    component[2]->input[0] = component[0];
    component[2]->input[1] = component[1];

    component[3]->input[0] = component[0]->input[0];
    component[3]->input[1] = component[1];

    component[4]->input[0] = component[0];
    component[4]->input[1] = component[1]->input[0];

    component[5]->input[0] = component[0]->input[0];
    component[5]->input[1] = component[1]->input[0];

    for (int i = 0; i < 4; i++) {
      enables[i]->input[0] = this->enable;
      enables[i]->input[1] = component[i + 2];
    }
  }
};

class Decoder4_16 : public Decoder {
 public:
  Decoder4_16() {}
  Decoder4_16(bool val) {}
  virtual void setEnable(bool val) {}
  virtual void setEnable(Gate *gate) {}
  virtual void setValue(bool val, int pin) {}
  virtual void setValue(Gate *gate, int pin) {}
  virtual Gate *operator[](int n) {}
  friend ostream &operator<<(ostream &out, Decoder4_16 dec) {}
  int output() {}

 private:
  Decoder *dec2_4[5];
};

class FourBitsRippleAdder : public Adder {};

class Decoder5_32 : public Decoder {};
