# Run through the Unreal MCP execute_python tool in a clean editor session.
MAP = '/Game/Fight/Maps/Lvl_FightGreybox'
TEMPLATE = '/Engine/Maps/Templates/Template_Default'

levels = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
editor = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem)
saving = unreal.EditorLoadingAndSavingUtils

if await call_tool('EditorToolset.EditorAppToolset.IsPIERunning'):
    raise RuntimeError('Stop PIE before creating the stage')
if saving.get_dirty_map_packages() or saving.get_dirty_content_packages():
    raise RuntimeError('Save any existing edits before creating the stage')
if await call_tool('EditorToolset.AssetToolset.Exists', path=MAP):
    raise RuntimeError('The greybox map already exists')

cube = unreal.load_asset('/Engine/BasicShapes/Cube.Cube')
game_mode = unreal.load_class(None, '/Script/FighterPrototype.FightGameMode')
if not cube or not game_mode or not levels.new_level_from_template(MAP, TEMPLATE):
    raise RuntimeError('Could not create the Basic greybox level')
if await call_tool('EditorToolset.LevelToolset.GetCurrentLevel') != MAP:
    raise RuntimeError('The greybox must be the active level')

for actor in actors.get_all_level_actors():
    if isinstance(actor, unreal.PlayerStart) or (isinstance(actor, unreal.StaticMeshActor) and actor.get_actor_label() == 'Floor'):
        if not actors.destroy_actor(actor):
            raise RuntimeError('Failed to remove a template placeholder')

def spawn(actor_class, label, location, rotation=None):
    actor = actors.spawn_actor_from_class(actor_class, unreal.Vector(*location), rotation or unreal.Rotator())
    if not actor:
        raise RuntimeError(f'Failed to place {label}')
    actor.set_actor_label(label)
    return actor

def block(label, location, scale):
    actor = spawn(unreal.StaticMeshActor, label, location)
    actor.static_mesh_component.set_static_mesh(cube)
    actor.static_mesh_component.set_collision_profile_name('BlockAll')
    actor.set_actor_scale3d(unreal.Vector(*scale))

block('StageFloor', (0, 0, -25), (16, 6, 0.5))
block('StageWallLeft', (-780, 0, 200), (0.4, 6, 4))
block('StageWallRight', (780, 0, 200), (0.4, 6, 4))

for slot, x, yaw in [('FighterA', -220, 0), ('FighterB', 220, 180)]:
    start = spawn(unreal.PlayerStart, slot + 'Start', (x, 0, 100), unreal.Rotator(yaw=yaw))
    start.set_editor_property('player_start_tag', slot)

camera = spawn(unreal.CameraActor, 'StageInspectionCamera', (0, -1800, 440), unreal.Rotator(pitch=-11, yaw=90))
view = camera.get_component_by_class(unreal.CameraComponent)
view.set_editor_property('projection_mode', unreal.CameraProjectionMode.ORTHOGRAPHIC)
view.set_editor_property('ortho_width', 1850.0)

settings = editor.get_editor_world().get_world_settings()
settings.set_editor_property('default_game_mode', game_mode)
if not saving.save_current_level():
    raise RuntimeError('Could not save the greybox level')

{'map': MAP, 'saved': True, 'game_mode': settings.default_game_mode.get_path_name()}
