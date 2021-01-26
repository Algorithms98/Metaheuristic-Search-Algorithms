//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#ifndef CODE_ALGORITHM_H
#define CODE_ALGORITHM_H


class Algorithm {
public:
    virtual Algorithm* Select(int)= 0;
    virtual void Execute() = 0;

};


#endif //CODE_ALGORITHM_H
