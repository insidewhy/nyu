#ifndef Pito_HPP
#define Pito_HPP

struct Pito {
    enum class Status {
        BAD,
        GOOD
    };

    enum class Panda {
        PAPANDA,
        KOPANDA
    };

    Pito()
      : status_(Status::GOOD),
        panda_(Panda::KOPANDA)
    {}
};

#endif
