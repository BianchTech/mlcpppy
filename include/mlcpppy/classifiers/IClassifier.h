class IClassifier {
    public:
        virtual void train() = 0; 
        virtual int predict() = 0;

        // Virtual destructor is important for proper cleanup when deleting through base pointer
        virtual IClassifier() {}
    };