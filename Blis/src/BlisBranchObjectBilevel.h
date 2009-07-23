/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Common Public License as part of the        *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           * 
 *                                                                           *
 * Copyright (C) 2001-2009, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/


//#############################################################################
// Borrow ideas from COIN/Cbc
//#############################################################################


#include "BcpsBranchObject.h"

#include "BlisModel.h"


//#############################################################################


class BlisBranchObjectBilevel : public BcpsBranchObject {

 protected:

    /** The indices of variables in the branching set. */
    std::deque<int> branchingSet_;
    
 public:
    
    /** Default constructor. */
    BlisBranchObjectBilevel() : BcpsBranchObject()
    {
	type_ = BlisBranchingObjectTypeBilevel;
    }

    /** Another useful constructor. */
    BlisBranchObjectBilevel(BcpsModel * model, std::deque<int> bs)
    : BcpsBranchObject(model)
    {
	type_ = BlisBranchingObjectTypeBilevel;
      	branchingSet_ = bs;
    }
    
    /** Copy constructor. */
    BlisBranchObjectBilevel(const BlisBranchObjectBilevel &);
    
    /** Assignment operator. */
    BlisBranchObjectBilevel & operator = (const BlisBranchObjectBilevel& rhs);
    
    /** Clone. */
    virtual BcpsBranchObject * clone() const {
        return (new BlisBranchObjectBilevel(*this));
    }

    /** Destructor. */
    virtual ~BlisBranchObjectBilevel() {}

    /** Get a pointer to the branching set */
    std::deque<int> getBranchingSet() const {return branchingSet_;}
    
    /** Set the bounds for the variable according to the current arm
	of the branch and advances the object state to the next arm.
	Returns change in guessed objective on next branch. */
    virtual double branch(bool normalBranch = false);

    /** \brief Print something about branch - only if log level high. */
    virtual void print(bool normalBranch);

 protected:

    /** Pack Blis portion to an encoded object. */
    AlpsReturnStatus encodeBlis(AlpsEncoded *encoded) const {
	assert(encoded);
	AlpsReturnStatus status = AlpsReturnStatusOk;
	return status;
    }

    /** Unpack Blis portion from an encoded object. */
    AlpsReturnStatus decodeBlis(AlpsEncoded &encoded) {
	AlpsReturnStatus status = AlpsReturnStatusOk;
	return status;
    }

 public:

    /** Pack to an encoded object. */
    virtual AlpsReturnStatus encode(AlpsEncoded *encoded) const {
	AlpsReturnStatus status = AlpsReturnStatusOk;

	status = encodeBcps(encoded);
	status = encodeBlis(encoded);
	
	return status;
    }

    /** Unpack a branching object from an encoded object. */
    virtual AlpsReturnStatus decode(AlpsEncoded &encoded) {
	
	AlpsReturnStatus status = AlpsReturnStatusOk;

	status = decodeBcps(encoded);
	status = decodeBlis(encoded);
	
	return status;
    }
    
};
