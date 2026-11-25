# Run through the Unreal MCP execute_python tool.
FOLDER = '/Game/Fight/Input'
MOVE = 'IA_FightMoveHorizontal'
JUMP = 'IA_FightJump'
CROUCH = 'IA_FightCrouch'
CONTEXT = 'IMC_FightKeyboard'

if await call_tool('EditorToolset.EditorAppToolset.IsPIERunning'):
    raise RuntimeError('Stop PIE before creating input assets')
for name in (MOVE, JUMP, CROUCH, CONTEXT):
    if await call_tool('EditorToolset.AssetToolset.Exists', path=f'{FOLDER}/{name}'):
        raise RuntimeError(f'Input asset already exists: {name}')

tools = unreal.AssetToolsHelpers.get_asset_tools()
assets = unreal.get_editor_subsystem(unreal.EditorAssetSubsystem)

def create(name, asset_class, factory):
    asset = tools.create_asset(name, FOLDER, asset_class, factory)
    if not asset:
        raise RuntimeError(f'Could not create {name}')
    return asset

move = create(MOVE, unreal.InputAction, unreal.InputAction_Factory())
move.set_editor_property('value_type', unreal.InputActionValueType.AXIS1D)
move.set_editor_property('accumulation_behavior', unreal.InputActionAccumulationBehavior.CUMULATIVE)
jump = create(JUMP, unreal.InputAction, unreal.InputAction_Factory())
crouch = create(CROUCH, unreal.InputAction, unreal.InputAction_Factory())
context = create(CONTEXT, unreal.InputMappingContext, unreal.InputMappingContext_Factory())

for name, action in [('A', move), ('D', move), ('W', jump), ('S', crouch)]:
    key = unreal.Key()
    key.set_editor_property('key_name', unreal.Name(name))
    context.map_key(action, key)

key_data = context.get_editor_property('default_key_mappings')
mappings = list(key_data.get_editor_property('mappings'))
left = next(mapping for mapping in mappings if str(mapping.key.get_editor_property('key_name')) == 'A')
negate = unreal.new_object(unreal.InputModifierNegate, outer=context)
left.set_editor_property('modifiers', [negate])
key_data.set_editor_property('mappings', mappings)
context.set_editor_property('default_key_mappings', key_data)

created = (move, jump, crouch, context)
for asset in created:
    if not assets.save_loaded_asset(asset, False):
        raise RuntimeError(f'Could not save {asset.get_path_name()}')
{'assets': [asset.get_path_name() for asset in created]}
