class Sub : public Super
{
    private:
        int subVal{0};
    public:
        Sub() {};
        Sub(int passedVal) : subVal{passedVal} {}
        int oneLess() {return (subVal - 1);}
};


