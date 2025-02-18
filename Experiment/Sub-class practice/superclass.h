class Super
{
    protected:
        int val{0};

    public:
        Super() {}
        Super(int passedVal) : val{passedVal} {}
        int getVal() {return val;}

};
