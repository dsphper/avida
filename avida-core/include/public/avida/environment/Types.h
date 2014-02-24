/*
 *  environment/Types.h
 *  avida-core
 *
 *  Created by David on 6/24/11.
 *  Copyright 2011 Michigan State University. All rights reserved.
 *  http://avida.devosoft.org/
 *
 *
 *  This file is part of Avida.
 *
 *  Avida is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 *  Avida is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License along with Avida.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors: David M. Bryson <david@programerror.com>
 *
 */

#ifndef AvidaEnvironmentTypes_h
#define AvidaEnvironmentTypes_h

#include "avida/core/Types.h"
#include "avida/structure/Types.h"
#include "avida/util/ArgParser.h"


namespace Avida {
  namespace Environment {
    
    // Class Declarations
    // --------------------------------------------------------------------------------------------------------------
    
    class ActionTrigger;
    class Context;
    class Library;
    class Manager;
    class Reaction;
    class ReactionProcess;
    class ReactionRequisite;
    class Resource;
    class ResourceDefinition;
    class ResourceListener;
    class ResourceManager;
    
    
    // Type Declarations
    // --------------------------------------------------------------------------------------------------------------
    
    typedef double ResourceQuantity;
    
    typedef Apto::String ActionTriggerID;
    typedef Apto::SmartPtr<ActionTrigger, Apto::ThreadSafeRefCount> ActionTriggerPtr;
    typedef Apto::SmartPtr<const ActionTrigger, Apto::ThreadSafeRefCount> ConstActionTriggerPtr;
    typedef Apto::Set<ActionTriggerID> ActionTriggerIDSet;
    typedef Apto::SmartPtr<ActionTriggerIDSet, Apto::ThreadSafeRefCount> ActionTriggerIDSetPtr;
    typedef Apto::SmartPtr<const ActionTriggerIDSet, Apto::ThreadSafeRefCount> ConstActionTriggerIDSetPtr;    
    typedef Apto::Set<ActionTriggerID>::ConstIterator ConstActionTriggerIDSetIterator;
    typedef Apto::Functor<bool, Apto::TL::Create</* setup arguments */> > ActionSetup;
    typedef Apto::Functor<double, Apto::TL::Create</* test arguments */> > ActionTest;

    typedef Apto::Functor<ReactionProcess*, Apto::TL::Create<Util::Args* /* setup arguments */> > ProcessCreate;

    typedef Apto::String ReactionID;
    typedef Apto::SmartPtr<Reaction, Apto::ThreadSafeRefCount> ReactionPtr;
    typedef Apto::SmartPtr<const Reaction, Apto::ThreadSafeRefCount> ConstReactionPtr;
    typedef Apto::Set<ReactionID> ReactionIDSet;
    typedef Apto::SmartPtr<ReactionIDSet, Apto::ThreadSafeRefCount> ReactionIDSetPtr;
    typedef Apto::SmartPtr<const ReactionIDSet, Apto::ThreadSafeRefCount> ConstReactionIDSetPtr;
    typedef Apto::Set<ReactionID>::ConstIterator ConstReactionIDSetIterator;
    
    
    
    typedef int ResourceID;
    typedef Apto::SmartPtr<Resource, Apto::ThreadSafeRefCount> ResourcePtr;
    typedef Apto::SmartPtr<const Resource, Apto::ThreadSafeRefCount> ConstResourcePtr;

    typedef Apto::Set<ResourceID> ResourceIDSet;
    typedef Apto::SmartPtr<ResourceIDSet, Apto::ThreadSafeRefCount> ResourceIDSetPtr;
    typedef Apto::SmartPtr<const ReactionIDSet, Apto::ThreadSafeRefCount> ConstResourceIDSetPtr;
    typedef Apto::Set<ResourceID>::ConstIterator ConstResourceIDSetIterator;
    
    typedef Apto::SmartPtr<Manager, Apto::InternalRCObject> ManagerPtr;
    
    
    typedef Apto::Functor<Resource*, Apto::TL::Create<ResourceDefinition&, Structure::Controller&> > ResourceCreateFunctor;
  };
};

#endif
