<?php

class local__interpro_results extends ChadoField {

  // The default lable for this field.
  public static $default_label = 'InterPro results';

  // The default description for this field.
  public static $description = 'Results for InterPro analysis.';

  // Provide a list of instance specific settings. These can be access within
  // the instanceSettingsForm.  When the instanceSettingsForm is submitted
  // then Drupal with automatically change these settings for the instnace.
  // It is recommended to put settings at the instance level whenever possible.
  // If you override this variable in a child class be sure to replicate the
  // term_name, term_vocab, term_accession and term_fixed keys as these are
  // required for all TripalFields.
  public static $default_settings  = array(
    // The short name for the vocabulary (e.g. shcema, SO, GO, PATO, etc.).
    'term_vocabulary' => 'local',
    // The name of the term.
    'term_name' => 'InterPro results',
    // The unique ID (i.e. accession) of the term.
    'term_accession' => 'interpro_results',
    // Set to TRUE if the site admin is allowed to change the term
    // type. This will create form elements when editing the field instance
    // to allow the site admin to change the term settings above.
    'term_fixed' => FALSE,
  );

  // The default widget for this field.
  public static $default_widget = 'local__interpro_results_widget';

  // The default formatter for this field.
  public static $default_formatter = 'local__interpro_results_formatter';

  /**
   * @see TripalField::load()
   */
  public function load($entity, $details = array()) {
    $record = $entity->chado_record;

    $field_name = $this->field['field_name'];

    // Set some defaults for the empty record.
    $entity->{$field_name}['und'][0] = array(
      'value' => ''
    );

    // Get the list of results.
    $interpro_results = tripal_get_interpro_XML_results($record->feature_id);
    if (is_array($interpro_results)) {
      $total = count($interpro_results);
      for ($delta = 0; $delta < $total; $delta++) {
        $results = $interpro_results[$delta];
        $entity->{$field_name}['und'][$delta] = array(
          'value' => $results->analysis->name,
          'parsed' => $results
        );
      }
    }
  }
}
