<?php
/**
 * @file
 *   Represents admin form for ding content related search.
 */

/**
 * Form handler for settings form.
 *
 * @param array $form
 *   Array of form elements.
 * @param array $form_state
 *   Array of form states.

 * @return array
 * Array of defined form elements.
 */
function ding_context_search_admin_settings($form, &$form_state) {
  $form['#tree'] = TRUE;
  $filters = variable_get('context_search_settings', '');

  $form['context_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#prefix' => '<div id="ding-context-search-filters-wrapper">',
    '#suffix' => '</div>',
    '#theme' => 'ding_context_search_table',
    '#desctiption' => t('Represents list of urls and related filter.'),
  );

  if (!isset($form_state['filters_count'])) {
    $form_state['filters_count'] = empty($filters) ? range(0, 0) : range(0, count($filters) - 1);
  }

  foreach ($form_state['filters_count'] as $key) {
    $form['context_search']['filters'][$key]['url'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($filters[$key]) ? $filters[$key]['url'] : '',
      '#required' => TRUE,
    );

    $form['context_search']['filters'][$key]['filter'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($filters[$key]) ? $filters[$key]['filter'] : '',
      '#required' => TRUE,
    );

    $form['context_search']['filters'][$key]['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#name' => 'filter_remove_' . $key,
      '#filter_key' => $key,
      '#submit' => array('ding_context_search_remove_filter_submit'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'wrapper' => 'ding-context-search-filters-wrapper',
        'callback' => 'ding_context_search_remove_ajax_handler',
      ),
    );
  }

  $form['context_search']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#name' => 'context_filter_add_btn',
    '#submit' => array('ding_context_search_add_submit'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'wrapper' => 'ding-context-search-filters-wrapper',
      'callback' => 'ding_context_search_add_ajax_handler',
    ),
  );

  $form['save_form'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for remove button.
 */
function ding_context_search_remove_filter_submit($form, &$form_state) {
  $element = $form_state['triggering_element'];
  unset($form_state['filters_count'][$element['#filter_key']]);
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax handler for remove button.
 */
function ding_context_search_remove_ajax_handler($form, &$form_state) {
  $element = $form_state['triggering_element'];
  $parents = $element['#parents'];
  $parents = array_slice($parents, 0, count($parents) - 3);
  return drupal_array_get_nested_value($form, $parents);
}

/**
 * Submit handler for adding filter.
 */
function ding_context_search_add_submit($form, &$form_state) {
  $id = !empty($form_state['filters_count']) ? max($form_state['filters_count']) + 1 : 1;
  $form_state['filters_count'][$id] = $id;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax handler for add button.
 */
function ding_context_search_add_ajax_handler($form, $form_state) {
  $element = $form_state['triggering_element'];
  $parents = $element['#parents'];
  array_pop($parents);
  return drupal_array_get_nested_value($form, $parents);
}

/**
 * Submit handler for saving settings.
 */
function ding_context_search_admin_settings_submit($form, &$form_state) {
  $wrapper = $form_state['values']['context_search']['filters'];
  foreach ($wrapper as &$item) {
    unset($item['remove']);
  }
  variable_set('context_search_settings', array_values($wrapper));
  drupal_set_message(t('Settings was successfully saved.'));
}
