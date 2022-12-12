﻿using System.Collections.Generic;
using System.Linq;
using StateSmith.compiler.Visitors;

namespace StateSmith.Compiling
{
    public class SpecificVertexValidator : VertexVisitor
    {
        public override void Visit(InitialState initialState)
        {
            ValidateInitialState(initialState);
            //no children to validate
        }

        public override void Visit(Vertex v)
        {
            throw new System.NotImplementedException();
        }

        public override void Visit(NamedVertex v)
        {
            throw new System.NotImplementedException();
        }

        public override void Visit(State v)
        {
            //FIXME finish
            VisitChildren(v);
        }

        public override void Visit(OrthoState v)
        {
            throw new System.NotImplementedException();
        }

        public override void Visit(Statemachine v)
        {
            if (v.Parent != null)
            {
                throw new VertexValidationException(v, "State machines cannot be nested, yet. See https://github.com/adamfk/StateSmith/issues/7");
            }

            // require initial state
            int initialStateCount = v.Children.OfType<InitialState>().Count();
            if (initialStateCount != 1)
            {
                throw new VertexValidationException(v, $"State machines must have exactly 1 initial state. Actual count: {initialStateCount}.");
            }

            VisitChildren(v);
        }

        public override void Visit(NotesVertex v)
        {
            if (v.IncomingTransitions.Count > 0)
            {
                throw new VertexValidationException(v, "Notes vertices cannot have any incoming transitions");
            }

            if (v.Behaviors.Count > 0)
            {
                throw new VertexValidationException(v, "Notes vertices cannot have any behaviors");
            }

            if (v.Children.Count > 0)
            {
                throw new VertexValidationException(v, "Notes vertices cannot have any children");
            }

            //note that transitions to state nodes within a notes node are caught when converting from Diagram nodes to Vertices
        }

        public override void Visit(EntryPoint entryPoint)
        {
            if (entryPoint.Children.Count > 0)
            {
                throw new VertexValidationException(entryPoint, "An entry point cannot have child states.");
            }

            if (entryPoint.Behaviors.Count != 1)
            {
                throw new VertexValidationException(entryPoint, $"An entry point must have only a single behavior (instead of {entryPoint.Behaviors.Count}) which is an outgoing transition (for now).");
            }

            var b = entryPoint.Behaviors[0];

            if (!b.HasTransition())
            {
                throw new VertexValidationException(entryPoint, "An entry point must have a single outgoing transition (for now).");
            }

            if (b.triggers.Count > 0)
            {
                throw new VertexValidationException(entryPoint, "An entry point transition cannot have a trigger/event.");
            }

            if (b.HasGuardCode())
            {
                throw new VertexValidationException(entryPoint, "An entry point transition cannot have any guard code (for now).");
            }

            if (entryPoint.Behaviors[0].TransitionTarget == entryPoint.Parent)
            {
                throw new VertexValidationException(entryPoint, $"An state's entry point transition cannot target itself.");
            }
        }

        public override void Visit(ExitPoint v)
        {
            if (v.Children.Count > 0)
            {
                throw new VertexValidationException(v, "An exit point cannot have child states.");
            }

            if (v.IncomingTransitions.Count == 0)
            {
                throw new VertexValidationException(v, "An exit point must at least one incoming transition (for now).");
            }
        }

        public static void ValidateInitialState(InitialState initialState)
        {
            InitialStateValidator.Validate(initialState);
        }

    }
}
