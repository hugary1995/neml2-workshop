nb = 5
nt = 100

[Tensors]
  [end_time]
    type = LogspaceScalar
    start = 2
    end = 5
    nstep = ${nb}
  []
  [times]
    type = LinspaceScalar
    start = 0
    end = end_time
    nstep = ${nt}
  []
  [exx]
    type = FullScalar
    batch_shape = '(${nb})'
    value = 0.2
  []
  [eyy]
    type = FullScalar
    batch_shape = '(${nb})'
    value = -0.1
  []
  [ezz]
    type = FullScalar
    batch_shape = '(${nb})'
    value = -0.1
  []
  [max_strain]
    type = FillSR2
    values = 'exx eyy ezz'
  []
  [strains]
    type = LinspaceSR2
    start = 0
    end = max_strain
    nstep = ${nt}
  []
  [a0]
    type = LinspaceScalar
    start = 600
    end = 1000
    nstep = ${nb}
  []
  [b]
    type = LinspaceScalar
    start = 0.03
    end = 0.06
    nstep = ${nb}
  []
[]

[Drivers]
  [driver]
    type = SolidMechanicsDriver
    model = 'model'
    times = 'times'
    prescribed_strains = 'strains'
    save_as = 'custom_isotropic_hardening.pt'
    predictor = 'LINEAR_EXTRAPOLATION'
    verbose = true
  []
[]

[Solvers]
  [newton]
    type = NewtonNonlinearSolver
    verbose = true
  []
[]

[Models]
  [a_T]
    type = ArrheniusLaw
    parameter = 'a'
    temperature = 'state/T'
    activation_energy = 200
    ideal_gas_constant = 8.314
    reference_value = 'a0'
  []
  ###############################################################################
  # Use the trial state to precalculate invariant flow directions
  # prior to radial return
  ###############################################################################
  [trial_elastic_strain]
    type = ElasticStrain
    plastic_strain = 'old_state/internal/Ep'
  []
  [cauchy_stress]
    type = LinearIsotropicElasticity
    youngs_modulus = 5e3
    poisson_ratio = 0.3
  []
  [mandel_stress]
    type = IsotropicMandelStress
  []
  [trial_isoharden]
    type = CustomIsotropicHardening
    equivalent_plastic_strain = 'old_state/internal/ep'
    a = 'a_T'
    b = 'b'
  []
  [vonmises]
    type = SR2Invariant
    invariant_type = 'VONMISES'
    tensor = 'state/internal/M'
    invariant = 'state/internal/sm'
  []
  [yield]
    type = YieldFunction
    yield_stress = 50
    isotropic_hardening = 'state/internal/k'
  []
  [flow]
    type = ComposedModel
    models = 'vonmises yield'
  []
  [normality]
    type = Normality
    model = 'flow'
    function = 'state/internal/fp'
    from = 'state/internal/M state/internal/k'
    to = 'forces/NM forces/Nk'
  []
  [trial_state]
    type = ComposedModel
    models = "trial_elastic_strain cauchy_stress mandel_stress
              a_T trial_isoharden normality"
  []
  ###############################################################################
  # The actual radial return:
  # Since the flow directions are invariant, we only need to integrate
  # the consistency parameter.
  ###############################################################################
  [trial_flow_rate]
    type = ScalarStateRate
    state = 'internal/gamma'
  []
  [plastic_strain_rate]
    type = AssociativePlasticFlow
    flow_direction = 'forces/NM'
  []
  [plastic_strain]
    type = SR2ForwardEulerTimeIntegration
    variable = 'internal/Ep'
  []
  [elastic_strain]
    type = ElasticStrain
  []
  [equivalent_plastic_strain_rate]
    type = AssociativeIsotropicPlasticHardening
    isotropic_hardening_direction = 'forces/Nk'
  []
  [equivalent_plastic_strain]
    type = ScalarForwardEulerTimeIntegration
    variable = 'internal/ep'
  []
  [isoharden]
    type = CustomIsotropicHardening
    a = 'a_T'
    b = 'b'
  []
  [surface]
    type = ComposedModel
    models = "trial_flow_rate
              plastic_strain_rate plastic_strain elastic_strain cauchy_stress mandel_stress
              equivalent_plastic_strain_rate equivalent_plastic_strain a_T isoharden
              vonmises yield"
  []
  [flow_rate]
    type = PerzynaPlasticFlowRate
    reference_stress = 100
    exponent = 2
  []
  [integrate_gamma]
    type = ScalarBackwardEulerTimeIntegration
    variable = 'internal/gamma'
  []
  [implicit_rate]
    type = ComposedModel
    models = "surface flow_rate integrate_gamma"
  []
  [return_map]
    type = ImplicitUpdate
    implicit_model = 'implicit_rate'
    solver = 'newton'
    additional_outputs = 'state/internal/gamma'
  []
  [model0]
    type = ComposedModel
    models = "trial_state return_map trial_flow_rate
              plastic_strain_rate plastic_strain
              equivalent_plastic_strain_rate equivalent_plastic_strain"
    additional_outputs = 'state/internal/Ep state/internal/ep'
  []
  [model]
    type = ComposedModel
    models = 'model0 elastic_strain cauchy_stress'
  []
[]
