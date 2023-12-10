# REMOVE_BEGIN
nbatch = 5
nstep = 51
tmax = 2

[Tensors]
  [end_time]
    type = LinspaceScalar
    start = ${tmax}
    end = ${tmax}
    nstep = ${nbatch}
  []
  [times]
    type = LinspaceScalar
    start = 0
    end = 'end_time'
    nstep = ${nstep}
  []
  [x0]
    type = Fill3DVec
    values = "0 11 0
              1 12 0
              2 13 0
              3 14 0
              4 15 0"
  []
  [v0]
    type = Fill3DVec
    values = "14 8 0
              12 7 0
              10 6 0
              8 5 0
              6 4 0"
  []
[]

[Drivers]
  [launcher]
    type = BallLauncher
    model = 'trajectory'
    position = 'state/x'
    velocity = 'state/v'
    initial_position = 'x0'
    initial_velocity = 'v0'
    times = 'times'
    save_as = 'flying_ball_in_air.pt'
    verbose = true
  []
[]

[Models]
  [ball]
    type = FlyingBall
    velocity = 'state/v'
    acceleration = 'state/a'
    # use_AD_first_derivative = true
    # use_AD_second_derivative = true
  []
  [position]
    type = VecBackwardEulerTimeIntegration
    variable = 'x'
    variable_rate = 'v'
    time = 't'
  []
  [velocity]
    type = VecBackwardEulerTimeIntegration
    variable = 'v'
    variable_rate = 'a'
    time = 't'
  []
  [implicit_trajectory]
    type = ComposedModel
    models = 'ball position velocity'
  []
  [trajectory]
    type = ImplicitUpdate
    implicit_model = 'implicit_trajectory'
    solver = 'newton'
  []
[]

[Solvers]
  [newton]
    type = NewtonNonlinearSolver
    verbose = true
    abs_tol = 1e-10
    rel_tol = 1e-8
    max_its = 100
  []
[]
# REMOVE_END
